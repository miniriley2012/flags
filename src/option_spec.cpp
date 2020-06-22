//
// Created by Riley Quinn on 6/14/20.
//

#include "flags/option_spec.hpp"

#include "flags/errors.hpp"

using namespace flags::errors;
using namespace std::string_literals;

flags::option_spec &flags::option_spec::add_option(flags::option option) {
    auto &name = option.name;
    if (name.length() > 2 && !name.starts_with("--")) {
        name.insert(0, "--");
    }
    if (options.contains(option.name))
        throw std::invalid_argument{"Found duplicate option '" + name + "'."};
    options[option.name] = option;
    if (option.shorthand != -1) {
        if (shorthand.contains(option.shorthand)) {
            throw std::invalid_argument{"Found duplicate shorthand option '-"s + option.shorthand + "' for " + name +
                                        ". It is currently assigned to " + shorthand[option.shorthand] + '.'};
        }
        shorthand[option.shorthand] = name;
    }
    return *this;
}

flags::parse_result flags::option_spec::parse(int argc, const char **argv) {
    parse_result result;

    if (argc < 2) {
        std::transform(options.begin(), options.end(), std::back_inserter(result.options),
                       [](auto pair) {
                           const auto &option = pair.second;
                           if (option.required) throw parse_error{missing_required, option};
                           return option;
                       });
        return result;
    }

    std::vector args(argv + 1, argv + argc);
    std::unordered_set<std::string> overrides;

    for (std::size_t i = 0; i < args.size(); i++) {
        std::string arg = args[i];

        if (arg == "--") {
            result.remaining.reserve(result.remaining.size() + (args.size() - i - 1));
            result.remaining.insert(result.remaining.end(), args.begin() + i + 1, args.end());
            break;
        }

        if (arg.starts_with("-") && arg.size() > 2 && arg[1] != '-') {
            for (std::size_t j = 1; j < arg.size(); j++) {
                if (shorthand.contains(arg[j])) {
                    if (auto &option = options[shorthand[arg[j]]]; option.has_value && j < arg.size() - 1) {
                        throw parse_error{missing_value, option, "-"s + arg[j]};
                    } else {
                        option.present = true;
                        overrides.merge(option.overrides);
                    }
                } else {
                    throw parse_error{undefined, std::nullopt, "-"s + arg[j]};
                }
            }
            arg = ("-") + arg.back();
        }
        if (arg.length() == 2 && shorthand.contains(arg[1])) arg = shorthand[arg[1]];
        if (options.contains(arg)) {
            auto &option = options[arg];
            option.present = true;
            overrides.merge(option.overrides);
            if (option.has_value) {
                i++;
                if (i > args.size() - 1) throw parse_error{missing_value, option};
                option.value = args[i];
            }
            if (option.validator && !option.validator(option)) throw parse_error{validation_error, option};
        } else {
            if (arg.starts_with("-")) throw parse_error{undefined, std::nullopt, arg};
            result.remaining.emplace_back(arg);
        }
    }

    for (const auto&[_, option] : options) {
        if (!(overrides.contains("*") || overrides.contains(option.name)) && option.required && !option.present)
            throw parse_error{missing_required, option};
        result.options.push_back(option);
    }

    return result;
}

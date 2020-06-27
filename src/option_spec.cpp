//
// Created by Riley Quinn on 6/14/20.
//

#include "options/option_spec.hpp"

#include "options/errors.hpp"

using namespace options::errors;
using namespace std::string_literals;

options::option_spec &options::option_spec::add_option(options::option option) {
    if (!option.default_value_.empty()) option.value_ = option.default_value_;
    auto &name = option.name_;
    if (name.length() > 2 && !name.starts_with("--")) {
        name.insert(0, "--");
    }
    if (options_.contains(option.name_))
        throw std::invalid_argument{"Found duplicate option '" + name + "'."};
    options_[option.name_] = option;
    if (option.shorthand_ != -1) {
        if (shorthand_.contains(option.shorthand_)) {
            throw std::invalid_argument{"Found duplicate shorthand option '-"s + option.shorthand_ + "' for " + name +
                                        ". It is currently assigned to " + shorthand_[option.shorthand_] + '.'};
        }
        shorthand_[option.shorthand_] = name;
    }
    return *this;
}

const std::map<std::string, options::option> &options::option_spec::get_options() {
    return options_;
}

options::parse_result options::option_spec::parse(int argc, const char **argv) {
    parse_result result;

    if (argc < 2) {
        std::transform(options_.begin(), options_.end(), std::inserter(result.options, result.options.begin()),
                       [](const auto &pair) -> decltype(result.options)::value_type {
                           const auto &option = pair.second;
                           if (option.required_) throw parse_error{missing_required, option};
                           return {option.name_, option};
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
                if (shorthand_.contains(arg[j])) {
                    if (auto &option = options_[shorthand_[arg[j]]]; option.has_value_ && j < arg.size() - 1) {
                        throw parse_error{missing_value, option, "-"s + arg[j]};
                    } else {
                        option.present_ = true;
                        std::copy(option.overrides_.begin(), option.overrides_.end(),
                                  std::inserter(overrides, overrides.begin()));
                    }
                } else {
                    throw parse_error{undefined, std::nullopt, "-"s + arg[j]};
                }
            }
            arg = ("-") + arg.back();
        }
        if (arg.length() == 2 && shorthand_.contains(arg[1])) arg = shorthand_[arg[1]];
        if (options_.contains(arg)) {
            auto &option = options_[arg];
            option.present_ = true;
            std::copy(option.overrides_.begin(), option.overrides_.end(),
                      std::inserter(overrides, overrides.begin()));
            if (option.has_value_) {
                i++;
                if (i > args.size() - 1) throw parse_error{missing_value, option};
                option.value_ = args[i];
            }
        } else {
            if (arg.starts_with("-")) throw parse_error{undefined, std::nullopt, arg};
            result.remaining.emplace_back(arg);
        }
    }

    for (const auto&[_, option] : options_) {
        const bool overridden = (overrides.contains("*") || overrides.contains(option.name_));
        if (!overridden && option.required_ && !option.present_)
            throw parse_error{missing_required, option};
        if (!overridden && option.validator_ && !option.validator_(option)) throw parse_error{validation_error, option};
        result.options[option.name_] = option;
    }

    return result;
}

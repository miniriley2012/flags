//
// Created by Riley Quinn on 6/14/20.
//

#include <options/option_spec.hpp>
#include <options/validations.hpp>
#include <iostream>

int main(int argc, const char **argv) {
    options::parse_result result = options::parse_options(
            options::option_spec{}
                    .add_option({
                                        .name = "--help",
                                        .shorthand = 'h',
                                        .usage = "Displays help menu",
                                        .overrides = {"*"}
                                })
                    .add_option({
                                        .name = "config",
                                        .shorthand = 'c',
                                        .has_value = true,
                                        .usage = "Path to config file",
                                        .validator = options::validations::file_exists
                                })
                    .add_option({
                                        .name = "--thing",
                                        .shorthand = 't',
                                        .has_value = true,
                                        .value = "test",
                                        .usage = "is a test thing",
                                        .required = true
                                }),
            argc, argv);

    for (const auto &opt : result.options) {
        std::cout << opt.name << "(" << (opt.present ? "p" : "!p") << ")" << ": "
                  << (opt.has_value ? (opt.value.empty() ? "empty" : opt.value) : "no value") << ", " << opt.usage
                  << "\n\n";
    }

    std::cout << "Remaining: [";
    for (std::size_t i = 0; i < result.remaining.size(); i++) {
        std::cout << result.remaining[i];
        if (i < result.remaining.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    return 0;
}
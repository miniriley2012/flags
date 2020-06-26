//
// Created by Riley Quinn on 6/14/20.
//

#ifndef OPTIONS_OPTION_SPEC_HPP
#define OPTIONS_OPTION_SPEC_HPP

#include "option.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace options {
    /// Contains the parsed options and the remaining arguments.
    struct parse_result {
        std::vector<option> options;
        std::vector<std::string> remaining;
    };

    /// Used to define options.
    class option_spec {
        std::map<std::string, option> options_;
        std::unordered_map<char, std::string> shorthand_;

    public:
        /// Adds an option to the option spec.
        /// \param option option to add
        /// \return reference to self
        option_spec &add_option(option option);

        /// Parses options in argv and returns a parse_result.
        /// \param argc argc from main
        /// \param argv argv from main
        /// \return parse_result containing the options and remaining arguments
        /// \throws runtime_exception any error in the flag::errors namespace.
        parse_result parse(int argc, const char **argv);
    };

    /// A convenience function that handles parsing errors by printing and exiting.
    /// \param spec an option_spec
    /// \param argc argc from main
    /// \param argv argv from main
    /// \return A parse_result containing the options and remaining arguments
    inline parse_result parse_options(option_spec spec, int argc, const char **argv) noexcept {
        try {
            return spec.parse(argc, argv);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            std::exit(1);
        }
    }
}

#endif //OPTIONS_OPTION_SPEC_HPP

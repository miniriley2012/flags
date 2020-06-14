//
// Created by Riley Quinn on 6/14/20.
//

#ifndef FLAGS_ERRORS_HPP
#define FLAGS_ERRORS_HPP

#include <stdexcept>

namespace flags::errors {
    /// Thrown when an option is found that wasn't defined in an option_spec.
    struct undefined_option : public std::runtime_error {
        explicit undefined_option(const std::string &found) :
                runtime_error("Undefined option '" + found + "' found.") {}
    };

    /// Thrown when a value is not given to a flag that requires one.
    struct missing_value : public std::runtime_error {
        explicit missing_value(const std::string &option_name) :
                runtime_error("Missing value for '" + option_name + "'.") {}
    };

    /// Thrown when a required flag is not found.
    struct missing_required : public std::runtime_error {
        explicit missing_required(const std::string &option_name) :
                runtime_error("Missing required option '" + option_name + "'") {}
    };

    struct duplicate_option : public std::runtime_error {
        explicit duplicate_option(const std::string &option_name) :
                runtime_error("Found duplicate option '" + option_name + "'.") {}
    };

    struct duplicate_shorthand : public std::runtime_error {
        duplicate_shorthand(char c, const std::string &option_name, const std::string &assigned = "")
                : runtime_error(
                std::string("Found duplicate shorthand option '-") + c + "' for " + option_name +
                "." + (assigned.empty() ? "" : " It is currently assigned to " + assigned + '.')) {}
    };

    struct validation_error : public std::runtime_error {
        explicit validation_error(std::string &option_name) :
                runtime_error("Validation failed for '" + option_name + "'.") {}
    };
}

#endif //FLAGS_ERRORS_HPP

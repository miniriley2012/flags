//
// Created by Riley Quinn on 6/14/20.
//

#ifndef OPTIONS_ERRORS_HPP
#define OPTIONS_ERRORS_HPP

#include "option.hpp"
#include <stdexcept>

namespace options::errors {
    enum option_error {
        undefined = 1,
        missing_value,
        missing_required,
        validation_error
    };

    /// Returns the name of an option_error.
    /// \param err option_error
    /// \return name of option error
    constexpr const char *option_error_str(const option_error err) {
        switch (err) {
            case undefined:
                return "option undefined";
            case missing_value:
                return "missing value";
            case missing_required:
                return "missing required";
            case validation_error:
                return "validation error";
            default:
                return "unknown error";
        }
    }

    /// Creates a custom error message for an option.
    /// \param err option_error for message
    /// \param option_name name of option
    /// \return custom error message
    std::string make_option_error_str(option_error err, const std::string &option_name);

    /// General struct for parsing errors.
    struct parse_error : std::runtime_error {
        const option_error type;
        const std::optional<options::option> option;

        // I know this is a mess. I might clean it up later.
        parse_error(const option_error type, const std::optional<options::option> &option, const std::string &value = "")
                : runtime_error(
                value.empty() ? option ? make_option_error_str(type, option->name) : option_error_str(type)
                              : make_option_error_str(type, value)),
                  type(type), option(option) {}
    };
}

#endif //OPTIONS_ERRORS_HPP

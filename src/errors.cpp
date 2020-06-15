//
// Created by Riley Quinn on 6/14/20.
//

#include "flags/errors.hpp"

std::string flags::errors::make_option_error_str(const option_error err, const std::string &option_name) {
    switch (err) {
        case undefined: {
            return "Undefined option '" + option_name + "'.";
        }
        case missing_value:
            return "Missing value for '" + option_name + "'.";
        case missing_required:
            return "Missing required option '" + option_name + "'.";
        case validation_error:
            return "Validation failed for '" + option_name + "'.";
        default:
            return "undefined error";
    }
}

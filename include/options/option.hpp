//
// Created by Riley Quinn on 6/14/20.
//

#ifndef OPTIONS_OPTION_HPP
#define OPTIONS_OPTION_HPP

#include <string>
#include <unordered_set>
#include <utility>

namespace options {
    /// Used in option_spec and validators.
    struct option {
        using overrides_type = std::unordered_set<std::string>;
        using validator_type = std::function<bool(option)>;

        std::string name;
        char shorthand = -1;
        bool has_value;
        std::string value;
        std::string usage;
        bool required;
        overrides_type overrides;
        validator_type validator;
        bool present;

        option &set_name(std::string_view option_name) {
            name = option_name;
            return *this;
        }

        option &set_shorthand(char option_shorthand) {
            shorthand = option_shorthand;
            return *this;
        }

        option &set_value(std::string_view option_value) {
            value = option_value;
            has_value = true;
            return *this;
        }

        option &clear_value() {
            has_value = false;
            return *this;
        }

        option &set_usage(std::string_view option_usage) {
            usage = option_usage;
            return *this;
        }

        option &set_required(bool option_required) {
            required = option_required;
            return *this;
        }

        option &set_overrides(overrides_type option_overrides) {
            overrides = std::move(option_overrides);
            return *this;
        }

        option &add_override(const std::string &option_override) {
            overrides.insert(option_override);
            return *this;
        }

        option &clear_overrides() {
            overrides.clear();
            return *this;
        }

        option &set_validator(const validator_type &option_validator) {
            validator = option_validator;
            return *this;
        }
    };
}

#endif //OPTIONS_OPTION_HPP

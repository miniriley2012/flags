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
        std::string default_value;
        std::string usage;
        bool required;
        overrides_type overrides;
        validator_type validator;
        bool present;
        std::string value;

        option &set_name(std::string_view option_name);

        option &set_shorthand(char option_shorthand);

        option &set_value(std::string_view option_value);

        option &clear_value();

        option &set_usage(std::string_view option_usage);

        option &set_required(bool option_required);

        option &set_overrides(overrides_type option_overrides);

        option &add_override(const std::string &option_override);

        option &clear_overrides();

        option &set_validator(const validator_type &option_validator);

        [[nodiscard]] constexpr bool has_shorthand() const {
            return shorthand > 0;
        }

        constexpr explicit operator bool() const {
            return present;
        }
    };
}

#endif //OPTIONS_OPTION_HPP

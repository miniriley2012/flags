//
// Created by Riley Quinn on 6/14/20.
//

#ifndef OPTIONS_OPTION_HPP
#define OPTIONS_OPTION_HPP

#include <string>
#include <unordered_set>
#include <utility>

namespace options {
    class option_spec;

    /// Used in option_spec and validators.
    class option {
        friend class option_spec;

    public:
        using overrides_type = std::unordered_set<std::string>;
        using validator_type = std::function<bool(option)>;

        option() = default;

        option(std::string_view name, std::string_view usage);

        option(std::string_view name, char shorthand, std::string_view usage);

        option &name(std::string_view name);

        [[nodiscard]] std::string name() const {
            return name_;
        }

        option &shorthand(char shorthand);

        [[nodiscard]] char shorthand() const {
            return shorthand_;
        }

        option &default_value(std::string_view value);

        [[nodiscard]] std::string default_value() const {
            return default_value_;
        }

        option &usage(std::string_view usage);

        [[nodiscard]] std::string usage() const {
            return usage_;
        }

        option &required(bool required);

        [[nodiscard]] bool required() const {
            return required_;
        }

        option &overrides(overrides_type overrides);

        [[nodiscard]] const overrides_type &overrides() const {
            return overrides_;
        }

        option &add_override(std::string_view override);

        option &validator(const validator_type &validator);

        [[nodiscard]] validator_type validator() const {
            return validator_;
        }

        [[nodiscard]] std::string value() const {
            return value_;
        }

        [[nodiscard]] constexpr bool present() const {
            return present_;
        }

        [[nodiscard]] constexpr bool has_value() const {
            return has_value_;
        }

        [[nodiscard]] constexpr bool has_shorthand() const {
            return shorthand_ > 0;
        }

        constexpr explicit operator bool() const {
            return present_;
        }

        constexpr std::string_view operator*() {
            return value_;
        }

    private:
        std::string name_;
        char shorthand_ = -1;
        bool has_value_ = false;
        std::string default_value_;
        std::string usage_;
        bool required_ = false;
        overrides_type overrides_;
        validator_type validator_;
        bool present_ = false;
        std::string value_;
    };
}

#endif //OPTIONS_OPTION_HPP

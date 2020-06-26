//
// Created by Riley Quinn on 6/26/20.
//

#include "options/option.hpp"

options::option &options::option::set_name(std::string_view option_name) {
    name = option_name;
    return *this;
}

options::option &options::option::set_shorthand(char option_shorthand) {
    shorthand = option_shorthand;
    return *this;
}

options::option &options::option::set_value(std::string_view option_value) {
    value = option_value;
    has_value = true;
    return *this;
}

options::option &options::option::clear_value() {
    has_value = false;
    return *this;
}

options::option &options::option::set_usage(std::string_view option_usage) {
    usage = option_usage;
    return *this;
}

options::option &options::option::set_required(bool option_required) {
    required = option_required;
    return *this;
}

options::option &options::option::set_overrides(options::option::overrides_type option_overrides) {
    overrides = std::move(option_overrides);
    return *this;
}

options::option &options::option::add_override(const std::string &option_override) {
    overrides.insert(option_override);
    return *this;
}

options::option &options::option::clear_overrides() {
    overrides.clear();
    return *this;
}

options::option &options::option::set_validator(const options::option::validator_type &option_validator) {
    validator = option_validator;
    return *this;
}

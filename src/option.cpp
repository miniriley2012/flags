//
// Created by Riley Quinn on 6/26/20.
//

#include "options/option.hpp"

options::option::option(std::string_view name, std::string_view usage) :
        name_{name},
        usage_{usage} {}

options::option::option(std::string_view name, char shorthand, std::string_view usage) :
        name_{name},
        shorthand_{shorthand},
        usage_{usage} {}

options::option &options::option::name(std::string_view name) {
    name_ = name;
    return *this;
}

options::option &options::option::shorthand(char shorthand) {
    shorthand_ = shorthand;
    return *this;
}

options::option &options::option::default_value(std::string_view value) {
    default_value_ = value;
    has_value_ = true;
    return *this;
}

options::option &options::option::usage(std::string_view usage) {
    usage_ = usage;
    return *this;
}

options::option &options::option::required(bool required) {
    required_ = required;
    return *this;
}

options::option &options::option::overrides(options::option::overrides_type overrides) {
    overrides_ = std::move(overrides);
    return *this;
}

options::option &options::option::add_override(std::string_view override) {
    overrides_.emplace(override);
    return *this;
}

options::option &options::option::validator(const options::option::validator_type &validator) {
    validator_ = validator;
    return *this;
}

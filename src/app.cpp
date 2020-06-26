//
// Created by Riley Quinn on 6/25/20.
//

#include "options/app.hpp"

std::string_view options::app::name() const {
    return name_;
}

options::app &options::app::name(std::string_view name) {
    name_ = name;
    return *this;
}

std::string_view options::app::description() const {
    return description_;
}

options::app &options::app::description(std::string_view description) {
    description_ = description;
    return *this;
}

std::string_view options::app::usage() const {
    return usage_;
}

options::app &options::app::usage(std::string_view usage) {
    usage_ = usage;
    return *this;
}

options::app &options::app::add_help_flag(const std::string &name = "help", char shorthand = 'h',
                                          const std::string &usage = "Shows this help menu") {
    spec_.add_option({
                             .name = name,
                             .shorthand = shorthand,
                             .usage = usage
                     });
    return *this;
}

std::string options::app::default_usage() {
    std::string result = name_;

    std::vector<std::string> options;

    for (const auto &[_, option] : spec_.get_options()) {
        std::string str;
        if (!option.required) {
            str += "[" + option.name;
            if (option.has_value) {
                str += " value";
            }
            str += "]";
        } else {
            str += option.name;
            if (option.has_value) {
                str += " value";
            }
        }
        options.push_back(str);
    }

    for (const auto &option : options) {
        result += " " + option;
    }

    return result + " args...";
}

std::string options::app::help() {
    const auto &options = spec_.get_options();
    std::size_t length = std::max_element(options.begin(), options.end(), [](auto a, auto b) {
        return a.first.length() < b.first.length();
    })->first.length() + 2;

    std::string result;
    result += name_ + "\n" + description_ + "\n\nUsage: " + (usage_.empty() ? default_usage() : usage_) + "\n";
    for (const auto &[_, option] : options) {
        result += "\t";
        if (option.has_shorthand()) {
            result += std::string("-") + option.shorthand + ", ";
        }
        result += option.name + std::string(length - option.name.length(), ' ') + option.usage;
        if (!option.default_value.empty() || !option.overrides.empty()) {
            result += " (";
            if (!option.value.empty()) {
                result += "default: \"" + option.default_value + "\"";
                if (!option.overrides.empty()) {
                    result += ", ";
                }
            }
            if (!option.overrides.empty()) {
                result += "overrides: {";
                for (auto it = option.overrides.begin(); it != option.overrides.end();) {
                    result += "\"" + (*it) + "\"";
                    if (++it != option.overrides.end()) {
                        result += ", ";
                    }
                }
                result += "}";
            }
            result += ")";
        }
        result += "\n";
    }

    return result;
}

options::app &options::app::option_spec(const options::option_spec &spec) {
    spec_ = spec;
    return *this;
}

options::option_spec &options::app::option_spec() {
    return spec_;
}
//
// Created by Riley Quinn on 6/14/20.
//

#ifndef FLAGS_OPTION_HPP
#define FLAGS_OPTION_HPP

#include <string>
#include <unordered_set>

namespace flags {
    /// Used in option_spec and validators.
    struct option {
        std::string name;
        char shorthand = -1;
        bool has_value;
        std::string value;
        std::string usage;
        bool required;
        std::unordered_set<std::string> overrides;
        std::function<bool(option)> validate;
        bool present;
    };
}

#endif //FLAGS_OPTION_HPP

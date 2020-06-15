//
// Created by Riley Quinn on 6/14/20.
//

#ifndef FLAGS_VALIDATIONS_HPP
#define FLAGS_VALIDATIONS_HPP

#include "option.hpp"

namespace flags::validations {
    [[maybe_unused]]
    bool number(const option &option);

    [[maybe_unused]]
    bool floating_point(const option &option);

    [[maybe_unused]]
    bool file_exists(const option &option);

    [[maybe_unused]]
    std::function<bool(flags::option)> file_extension(const std::string &extension);
}

#endif //FLAGS_VALIDATIONS_HPP

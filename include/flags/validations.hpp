//
// Created by Riley Quinn on 6/14/20.
//

#ifndef FLAGS_VALIDATIONS_HPP
#define FLAGS_VALIDATIONS_HPP

#include "option.hpp"

namespace flags::validations {
    bool number(const option &option);

    bool floating_point(const option &option);

    bool file_exists(const option &option);

    std::function<bool(option)> file_extension(const std::string &extension);
}

#endif //FLAGS_VALIDATIONS_HPP

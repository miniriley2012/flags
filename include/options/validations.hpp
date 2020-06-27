//
// Created by Riley Quinn on 6/14/20.
//

#ifndef OPTIONS_VALIDATIONS_HPP
#define OPTIONS_VALIDATIONS_HPP

#include "option.hpp"

namespace options::validations {
    [[maybe_unused]]
    bool number(const option &option);

    [[maybe_unused]]
    bool floating_point(const option &option);

    [[maybe_unused]]
    bool file_exists(const option &option);

    [[maybe_unused]]
    bool file_not_exists(const option &option);

    [[maybe_unused]]
    std::function<bool(options::option)> file_extension(const std::string &extension);
}

#endif //OPTIONS_VALIDATIONS_HPP

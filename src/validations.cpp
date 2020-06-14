//
// Created by Riley Quinn on 6/14/20.
//

#include "flags/validations.hpp"

#include <filesystem>

bool flags::validations::number(const flags::option &option) {
    const auto &value = option.value;
    return !value.empty() && std::all_of(value.begin(), value.end(), isdigit);
}

bool flags::validations::floating_point(const flags::option &option) {
    const auto &value = option.value;
    return !value.empty() && std::count(value.begin(), value.end(), '.') == 1 &&
           std::all_of(value.begin(), value.end(), [](char c) { return isdigit(c) || c == '.'; });
}

bool flags::validations::file_exists(const flags::option &option) {
    return std::filesystem::exists(option.value);
}

std::function<bool(flags::option)> flags::validations::file_extension(const std::string &extension) {
    return [&extension](const option &option) {
        return std::filesystem::path(option.value).extension() == extension;
    };
}

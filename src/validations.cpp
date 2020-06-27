//
// Created by Riley Quinn on 6/14/20.
//

#include "options/validations.hpp"

#include <filesystem>

[[maybe_unused]]
bool options::validations::number(const options::option &option) {
    const auto &value = option.value();
    return !value.empty() && std::all_of(value.begin(), value.end(), isdigit);
}

[[maybe_unused]]
bool options::validations::floating_point(const options::option &option) {
    const auto &value = option.value();
    return !value.empty() && std::count(value.begin(), value.end(), '.') == 1 &&
           std::all_of(value.begin(), value.end(), [](char c) { return isdigit(c) || c == '.'; });
}

[[maybe_unused]]
bool options::validations::file_exists(const options::option &option) {
    return std::filesystem::exists(option.value());
}

bool options::validations::file_not_exists(const options::option &option) {
    return !file_exists(option);
}

[[maybe_unused]]
std::function<bool(options::option)> options::validations::file_extension(const std::string &extension) {
    return [&extension](const option &option) {
        return std::filesystem::path(option.value()).extension() == extension;
    };
}

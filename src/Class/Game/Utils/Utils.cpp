//
// Created by sylvi on 14/09/2026.
//

#include "Utils.h"

#include <optional>
#include <sstream>
#include <c4/substr.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp>
#include <c4/yml/file.hpp>

std::string Utils::csubtrToString(const c4::csubstr& csubstr) {
    std::stringstream ss;
    ss << csubstr;
    return ss.str();
}

std::optional<std::string> Utils::getFileContent(const std::string &filePath) {
    try {
        return ryml::file_get_contents<std::string>(filePath.c_str());
    } catch (...) {
        return {};
    }
    return {};
}

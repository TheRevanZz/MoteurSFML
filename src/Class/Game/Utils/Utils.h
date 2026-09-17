//
// Created by sylvi on 14/09/2026.
//

#pragma once


#include <string>
#include <c4/substr_fwd.hpp>
#include <optional>

namespace Utils {
    std::string csubtrToString(const c4::csubstr& csubstr);

    std::optional<std::string> getFileContent(const std::string& filePath);

}

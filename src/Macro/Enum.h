//
// Created by sylvi on 14/09/2026.
//

#pragma once

#include <string>

#define DEFINE_ENUM(enum_name, ...) \
    enum class enum_name { \
        __VA_ARGS__ \
    }; \
    \
    std::string[] Get##enum_name##Keys(){ \
        return [__VA_ARGS__]; \
    }


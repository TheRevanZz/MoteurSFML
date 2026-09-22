//
// Created by sylvi on 14/09/2026.
//

#pragma once
#include <array>
#include <optional>
#include <string>
#include <string_view>

#define KEY_TAG \
    X(UP) \
    X(DOWN) \
    X(LEFT) \
    X(RIGHT) \
    X(DASH) \
    X(SHOOT)

enum class EActionTag {
    #define X(value) value,
        KEY_TAG
    #undef X
};

inline std::optional<std::string> EActionTagToString(const EActionTag tag) {
    switch (tag) {
        #define X(tag) \
            case EActionTag::tag: \
                return #tag;
            KEY_TAG
        #undef X
    }
    return {};
}

inline std::optional<EActionTag> StringToEActionTag(const std::string& string) {

    #define X(tag) \
            if (string == #tag) \
                return EActionTag::tag;
        KEY_TAG
    #undef X
    return {};
}

// inline std::vector<std::string> GetEKeyTagsValues() {
//     return
//         #define X(value) #value,
//             { KEY_TAG }
//         #undef X
//     ;
// }

constexpr auto GetEActionTagsValues() {
    return std::array{
        #define X(value) std::string_view(#value),
                 KEY_TAG
        #undef X
    };
}
#pragma once
#include <cstdint>
#include <functional>
#include <unordered_map>

namespace se3
{
    /*
     * Stocke des keyframes (en %) avec des actions qui seront effectué a ses keyframes
     */
    using AnimationFunc = std::function<void()>;
    using AnimationKeyframeType = uint8_t;
    using AnimationCourbe = std::unordered_map<AnimationKeyframeType, AnimationFunc>;
}

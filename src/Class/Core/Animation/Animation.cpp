#include "Animation.h"

#include <algorithm>
#include <cmath>
#ifndef NDEBUG
#include <iostream>
#endif
#include <ranges>

#include "Debug.h"
#include "Game/Time/Time.h"

se3::Animation::Animation(
    AnimationCourbe animationCourbe,
    StopAnimationCallback_T stopAnimationCallback,
    const float animationDuration
)
    : _animationCourbe(std::move(animationCourbe)),
      _stopAnimationCallback(std::move(stopAnimationCallback)),
      _animationDuration(animationDuration)
{
    
    const auto& keyframes_view = _animationCourbe | std::views::keys;
    _keyframes.reserve(keyframes_view.size());
    
    for (const auto& key : keyframes_view)
    {
        _keyframes.emplace_back(key);
    }

    std::ranges::sort(_keyframes);
}

void se3::Animation::Animate()
{
    
    const uint8_t currentProgression = static_cast<uint8_t>(
        std::round(_animationElapsedTime / _animationDuration * 100)
    );

    DEBUG_ONLY(
        std::cout << "progression : " << static_cast<int>(currentProgression) << "\n";
    )

    if (_currentKey >= _keyframes.size())
    {
        StopAnimation();
        return;
    }

    if (_keyframes[_currentKey] <= currentProgression)
    {
        _animationCourbe.at(_keyframes[_currentKey])();
        _currentKey++;
    }

    _animationElapsedTime += Time::deltaTime();
    if (_animationElapsedTime > _animationDuration)
    {
        StopAnimation();
    }
}

void se3::Animation::StopAnimation()
{
    _animationElapsedTime = 0.f;
    _currentKey = 0.f;

    _stopAnimationCallback();
}

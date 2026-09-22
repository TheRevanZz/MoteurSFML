#pragma once
#include "Courbe/AnimationCourbe.h"

namespace se3
{
    class Animation
    {
        
        using StopAnimationCallback_T = std::function<void()>;
        
    public:
        virtual ~Animation() = default;
        Animation(AnimationCourbe animationCourbe,  StopAnimationCallback_T stopAnimationCallback, float animationDuration);
        
        virtual void Animate();
        
    protected:
        
        AnimationCourbe _animationCourbe;
        std::vector<AnimationKeyframeType> _keyframes = {};
        StopAnimationCallback_T _stopAnimationCallback;
        
        float _animationDuration;
        float _animationElapsedTime = 0.0f;
        size_t _currentKey = 0;
        
        virtual void StopAnimation();
    };
}

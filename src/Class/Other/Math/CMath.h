#pragma once

class CMath
{
public:
    static bool floatEqual(float a, float b);
    
    template<typename T>
    static T toNegatif(T value);
    
    template<typename T>
    static T toPositif(T value);
    static float randf(float min, float max);
};

template <typename T>
T CMath::toNegatif(T value)
{
    if (value < 0)
        return value;
    return -value;
}

template <typename T>
T CMath::toPositif(T value)
{
    if (value > 0)
        return value;
    return -value;
}

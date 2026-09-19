#include "CoordinateSystem.h"

#include "Game/WindowData/WindowData.h"

CoordinateSystem::ScreenPoint CoordinateSystem::ToScreenPoint(const WorldPoint& worldPoint)
{
    const auto screenSize = WindowData::GetScreenSize();
    return {
        static_cast<int>(screenSize.x / 2) + static_cast<int>(worldPoint.x),
        static_cast<int>(screenSize.y) - (static_cast<int>(worldPoint.y) + static_cast<int>(screenSize.y / 2))
    };
}

CoordinateSystem::WorldPoint CoordinateSystem::ToWorldPoint(const ScreenPoint& screenPoint)
{
    const auto screenSize = WindowData::GetScreenSize();
    return {
        static_cast<float>(screenPoint.x) - static_cast<float>(screenSize.x) / 2.f,
       static_cast<float>(screenSize.y) / 2.f - static_cast<float>(screenPoint.y)
    };
}

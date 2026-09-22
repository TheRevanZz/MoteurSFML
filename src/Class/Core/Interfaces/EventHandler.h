#pragma once


class IEventHandler
{

public:
    virtual ~IEventHandler() = default;
    virtual void ProcessEvent() = 0;
};

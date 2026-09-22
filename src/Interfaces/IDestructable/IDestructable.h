//
// Created by sylvi on 15/09/2026.
//

#pragma once


class IDestructable {

public:
    virtual ~IDestructable() = default;

    virtual void Destruct() = 0;
};


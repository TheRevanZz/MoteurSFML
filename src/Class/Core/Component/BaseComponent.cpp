#include "BaseComponent.h"

const IGameComponent* se3::BaseComponent::GetParent() const
{
    return _parent;
}

se3::BaseComponent::BaseComponent(IGameComponent* owner)
    : _parent(owner)
{
}

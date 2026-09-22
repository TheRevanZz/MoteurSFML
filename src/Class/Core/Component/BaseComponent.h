#pragma once

class IGameComponent;

#include <utility>
#include <memory>

namespace se3
{
    
    class BaseComponent
    {
    public:
        [[nodiscard]] const IGameComponent* GetParent() const;

    protected:
        explicit BaseComponent(IGameComponent* owner);

    private:
        IGameComponent* _parent = nullptr;
    };

    template <typename T>
    concept BaseComponent_t = std::derived_from<T,BaseComponent>;

    template <BaseComponent_t T, typename... Args>
        requires std::constructible_from<T, Args...>
    std::shared_ptr<T> CreateComponent(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

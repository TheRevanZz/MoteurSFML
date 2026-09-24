#pragma once

#include <vector>
#include "Ennemy.h"

using ComponentsList = std::vector<std::shared_ptr<IGameComponent>>;

class EnnemyFactory : public IUpdateable
{
    std::vector<std::shared_ptr<Ennemy>> _ennemies;
    
public:
    EnnemyFactory();
    
    const std::vector<std::shared_ptr<Ennemy>>& GetEnnemies() const { return _ennemies; }

    void SetComponentsList(ComponentsList* components);
    ComponentsList* GetComponentsList() const;

   void CreateEnnemy();

    void update() override;
    
protected:

    std::vector<std::shared_ptr<Ennemy>> _ennemiesTemplate;

    ComponentsList* _pComponents = nullptr;

    // à réfléchir
    sf::Texture _ennemyTexture;

    sf::Time _generationTimer;
    sf::Clock _clock;
};
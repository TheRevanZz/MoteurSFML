#pragma once

#include <vector>
#include "Ennemy.h"

class EnnemyFactory
{
    std::vector<std::shared_ptr<Ennemy>> _ennemies;
    
public:
    EnnemyFactory();
    
    const std::vector<std::shared_ptr<Ennemy>>& GetEnnemies() const { return _ennemies; }
    
private:
    
    std::vector<std::shared_ptr<Ennemy>> _ennemiesTemplate;
};









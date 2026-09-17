#pragma once
#include <memory>
#include <vector>

#include "Ennemy.h"

class EnnemyFactory
{
    using ennemiesList = std::vector<std::unique_ptr<Ennemy>>;
    
    ennemiesList _ennemies;
    
public:
    EnnemyFactory();
    
    const ennemiesList& getEnnemies() const { return _ennemies; }
};









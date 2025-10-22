
#pragma once
#include "Enemy.h"

class Slime : public Enemy {
public:
    Slime(int x,int y) : Enemy(x,y,'S',"Slime",3,2) {} // Calls the based class constructor
protected:
    void doMoveAttack(class Game& game, bool attackWindow) override; // Decide Enemy acion each turn, Game& game takes the current game state
};

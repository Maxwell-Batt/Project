
#pragma once
#include "Enemy.h" // Include the base class header

// Base class Enemy with Subclass Archer, example of Inheritance
class Archer : public Enemy {
public:
    Archer(int x,int y) : Enemy(x,y,'A',"Archer",2,2) {} // Calls the based class constructor with fixed stats.
protected:
    // Decide Enemy acion each turn, Game& game takes the current game state
    // as a parameter and a bool which tells enemt it must attack every second turn.
    // override tells the compiler this function must match a virtual function in the base class.
    void doMoveAttack(class Game& game, bool attackWindow) override; 
};

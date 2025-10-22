
#pragma once
#include "Actor.h"

class Enemy : public Actor {
protected:
    int turnCounter; // Counts turns to manage attack windows
public: 
    // Iniitializer list to set up base Actor attributes
    Enemy(int x,int y,char g,std::string n,int hp_,int dmg)
    : Actor(x,y,g,std::move(n),hp_,dmg), turnCounter(0) {} // Initialize turnCounter to 0
    virtual ~Enemy() = default; // Virtual destructor for cleanup to avoid memory leaks.
    // Uses polymorphism per turn and 
    // overrides base virtual to encapsulate 
    // enemy move or attack using the current Game state (no return).
    void takeTurn(class Game& game) override; 

protected:
// Virtual behabiour, forces subclass move or attack 
// logic using the Game state and enables polymorphism.
    virtual void doMoveAttack(class Game& game, bool attackWindow) = 0;
};

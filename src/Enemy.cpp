
#include "Enemy.h"
#include "Game.h"

void Enemy::takeTurn(Game& game) { 
    ++turnCounter; // Increment turn counter
    bool attackWindow = (turnCounter % 2 == 0); // can act offensively every 2nd turn
    doMoveAttack(game, attackWindow); // this function is polymorphic based on Enemy subclass
}

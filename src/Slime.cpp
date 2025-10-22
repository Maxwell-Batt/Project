
#include "Slime.h"
#include "Game.h"
#include <cmath>
#include <vector>

static int sgn(int v){ return (v>0) - (v<0); } //static function to get the sign of an integer

void Slime::doMoveAttack(Game& game, bool attackWindow) { //Method defining Slime's behavior each turn
    auto& player = game.getPlayer(); // Get reference to the player
    int dx = player.x() - x(); // Calculate distance to player
    int dy = player.y() - y(); // Calculate distance to player
    int manhattan = std::abs(dx) + std::abs(dy); // Calculate Absolute distance to player

    if (attackWindow && manhattan == 1) { //If adjacent to player and it's an attack turn
        // Attack
        player.takeDamage(getDamage()); // Inflict damage to player using Actor method
        return;
    }

    // Move towards player by one step if possible 
    int stepX = sgn(dx), stepY = sgn(dy);  // Determine step direction
    // Try horizontal move first randomly
    if (std::abs(dx) >= std::abs(dy)) { //if horizontal distance greater than vertical
        if (game.moveActor(*this, stepX, 0)) return; // Try moving horizontally
        (void)game.moveActor(*this, 0, stepY); // Else try moving vertically
    } else { //if vertical distance greater than horizontal
        if (game.moveActor(*this, 0, stepY)) return; // Try moving vertically
        (void)game.moveActor(*this, stepX, 0); // Else try moving horizontally
    }
}

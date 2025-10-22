
#include "Archer.h"
#include "Game.h"
#include <cmath> // For std::abs

static int sgn(int v){ return (v>0) - (v<0); } // Sign function

// Method and Definition of Archer's attack and movement logic
void Archer::doMoveAttack(Game& game, bool attackWindow) { 
    auto& map = game.getMap(); // Get reference to the map
    auto& player = game.getPlayer(); // Get reference to the player
    int dx = player.x() - x(); // Calculates horizontal distance to player using accessor
    int dy = player.y() - y(); // Calculates vertical distance to player using accessor
    int manhattan = std::abs(dx) + std::abs(dy); // Calculates the absolute distance to player

    // Attack if exactly 2 tiles away in straight line, with clear line of sight every 2nd turn
    if (attackWindow && map.hasLineOfSight(x(), y(), player.x(), player.y())) { // Check line of sight, 
        // Attack only if this is an attack turn AND player is 2 tiles away in a clear straight line.

        player.takeDamage(getDamage()); // Inflict damage to player using Actor method
        return;
    }

    // Otherwise, try to position to distance 2 straight line
    // Move towards aligning row or col while keeping some space
    int moveX = 0, moveY = 0; // Movement postions

    if (x() != player.x()) moveX = sgn(dx); // If not aligned horizontally, move towards player
    else if (y() != player.y()) moveY = sgn(dy); // If not aligned vertically, move towards player

    // If too close, adjacent in this case, back off if possible
    if (manhattan == 1) {
        moveX = -sgn(dx); // Back off horizontally
        moveY = -sgn(dy); // Back off vertically
    }

    //this represents an implicit pointer to a function that takes two integers as parameters and returns a boolean value.
    if (moveX != 0 && game.moveActor(*this, moveX, 0)) return; // if can move horizontally, do it
    if (moveY != 0 && game.moveActor(*this, 0, moveY)) return; // if can move vertically, do it

    // Last resort is to try a perpendicular dodge
    if (std::abs(dx) >= std::abs(dy)) { // if absolute horizontal distance greater than vertical
        if (game.moveActor(*this, 0, 1)) return; // if game move vertically down works, do it
        (void)game.moveActor(*this, 0, -1); // else try moving vertically up
    } else {
        if (game.moveActor(*this, 1, 0)) return; // if game move horizontally right works, do it
        (void)game.moveActor(*this, -1, 0); // else try moving horizontally left
    }
}

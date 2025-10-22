
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cctype> // For std::tolower, converts single character to lowercase

bool Player::usePotion() { // Use a potion if available
    if (potions <= 0) return false; // No potions left
    --potions; // Decrease potion count
    heal(9); // Heal player by 9 HP
    return true; // Potion used successfully
}

void Player::takeTurn(Game& game) { // Player's turn logic
    std::cout << "Move (WASD), [F]ight, [E]lixir, [Q]uit: "; // Prompt for player action
    std::string line; // Input line
    if (!std::getline(std::cin, line)) { game.requestQuit(); return; } // If input fails, request quit
    if (line.empty()) return; // No input, do nothing
    char c = std::tolower(line[0]); // Convert first character to lowercase
    bool acted = false; // Flag to track if player acted this turn
    switch (c) { // Handle player input
        case 'w': acted = game.moveActor(*this, 0, -1); break; // when w is pressed, move up one tile
        case 's': acted = game.moveActor(*this, 0,  1); break; // when s is pressed, move down one tile
        case 'a': acted = game.moveActor(*this, -1, 0); break; // when a is pressed, move left one tile
        case 'd': acted = game.moveActor(*this,  1, 0); break; // when d is pressed, move right one tile
        case 'e': // Use potion
            if (usePotion()) { std::cout << "You drink a potion (+9 HP).\n"; acted = true; } // if potion used successfully
            else std::cout << "No potions left!\n"; // else no potions message
            break;
        case 'f': { 
            // Attack an adjacent enemy, prefer up, down, left or right
            static const int dd[4][2] = {{0,-1},{0,1},{-1,0},{1,0}}; // Directions for up, down, left, right
            for (auto &d : dd) { // for each direction
                int tx = x() + d[0], ty = y()+d[1]; // target coordinates
                if (auto* foe = game.enemyAt(tx,ty)) { // if enemy at target
                    foe->takeDamage(getDamage()); // Inflict damage to enemy using Actor method
                    std::cout << "You hit the " << foe->getName() << " for " << getDamage() << ".\n"; // Print hit message
                    acted = true; // Mark that player acted
                    if (!foe->isAlive()) { // if enemy defeated
                        std::cout << foe->getName() << " defeated!\n"; // Print defeated message
                        addScore(10); // Add score for defeating enemy
                        game.onEnemyDefeated(); // Notify game of enemy defeat
                    }
                    break;
                }
            }
            if (!acted) std::cout << "No enemy adjacent.\n"; // If no adjacent enemy, print message
        } break;
        case 'q':
            game.requestQuit(); acted = true; break; // Request to quit the game
        default:
            std::cout << "Invalid input. Use WASD/F/E/Q.\n"; // Invalid input message
    }
    (void)acted; // Suppress unused variable warning
}

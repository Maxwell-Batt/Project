
#include "Game.h"
#include <iostream>
#include <random> // For std::random_device

int main() {
    // Fixed size map, deterministic seed optional
    unsigned seed = std::random_device{}(); // You can replace with a fixed number for reproducible runs
    Game game(16, 8, seed); // Create game with 16x8 map
    try { // try means something under may fail, catch will handle it.
        game.start(); // Start the game
    } catch (const std::exception& e) { // Catch any standard exceptions
        std::cerr << "Fatal error: " << e.what() << "\n"; // Print error message to standard error
        return 1; // Return non-zero to indicate failure
    }
    return 0; // Return zero to indicate success
}


#pragma once
#include <vector> // For std::vector
#include <memory> // For std::unique_ptr
#include <random> // For std::mt19937
#include <optional> // For std::optional
#include "Map.h" // Include Map class
#include "Player.h" // Include Player class
#include "Slime.h" // Include Slime class
#include "Archer.h" // Include Archer class
#include "Potion.h"// Include Potion class
#include "Scoreboard.h" // Include Scoreboard class

class Game {
    Map map; // The game map
    Player player; // The player character
    std::vector<std::unique_ptr<Enemy>> enemies; //List of enemies as unique pointers in a vector.
    std::unique_ptr<Potion> potion; // Unique pointer to a Potion object
    int round; // Current round number
    int turn; // Current turn number
    std::mt19937 rng; // Random number generator
    Scoreboard board; // Scoreboard to track high scores
    bool quitRequested; // Flag to indicate if quit is requested
public:
    Game(int w,int h,unsigned seed=std::random_device{}()); // Constructor with map dimensions and RNG seed

    void start(); // Start the game
    void gameLoop(); // Main game loop
    void nextRound(); // Proceed to the next round
    void render(); // Render the game state
    void renderHUD(); // Render the HUD
    bool moveActor(Actor& a, int dx, int dy); // Move an actor by dx, dy
    bool isOccupied(int x,int y) const; // Check if a position is occupied
    Enemy* enemyAt(int x,int y) const; // Get enemy at a position
    Potion* potionAt(int x,int y) const; // Get potion at a position
    const Map& getMap() const { return map; } // Get constant reference to the map
    Player& getPlayer() { return player; } // Get reference to the player
    int getTurn() const { return turn; } // Get current turn number
    int getRound() const { return round; } // Get current round number
    std::mt19937& getRng() { return rng; } // Get reference to the RNG
    void onEnemyDefeated(); // Handle enemy defeat
    void placePotionRandom(); // Place a potion at a random location
    void spawnEnemiesForRound(); // Spawn enemies for the current round
    void finishGame(bool victory); // Finish the game with victory or defeat
    void requestQuit() { quitRequested = true; } // Request to quit the game
    bool isQuitRequested() const { return quitRequested; } // Check if quit is requested
};

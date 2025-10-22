
#pragma once
#include "Actor.h"

class Player : public Actor {
    int potions; // Number of potions the player has
    int score; // Player's score
public:
    Player(int x,int y) : Actor(x,y,'@',"Runner",10,5), potions(1), score(0) {} // Initialize with 1 potion and 0 score, and actor with fixed stats.
    int getPotions() const { return potions; } // Getter for number of potions
    int getScore() const { return score; } // Getter for score
    void addScore(int s) { score += s; } // Add to score
    void addPotion(int n) { potions += n; } // Add potions
    bool usePotion(); // Use a potion if available
    void takeTurn(class Game& game) override; // Player's turn logic
};

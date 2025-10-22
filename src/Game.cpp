
#include "Game.h"
#include <iostream>
#include <iomanip> // For std::setw, sets minimum width of output for next thing to print
#include <algorithm> // For std::remove_if, for removing dead enemies
#include <chrono> // For seeding RNG

Game::Game(int w,int h,unsigned seed) // Constructor with map dimensions and RNG seed
: map([&]{ std::mt19937 tmp(seed); return Map(w,h,(w*h)/20,tmp); }()), // Generate map with obstacles
  player(w/2, h-2), // Initialize player in center bottom
  enemies(), // Empty enemy list
  potion(nullptr), // No potion at start
  round(1), // Start at round 1
  turn(0), // Start at turn 0
  rng(seed), // Initialize RNG with seed
  board("scores.txt"), // Scoreboard file
  quitRequested(false) // No quit requested at start
{
    // Ensure starting tile is walkable
    (void)0;
}

void Game::start() {
    // Main menu
    while (true) {
        std::cout << "\n=== Rogue Runner ===\n"
                  << "1) Start Game\n"
                  << "2) High Scores\n"
                  << "3) Quit\n"
                  << "Select: ";
        std::string line;
        if (!std::getline(std::cin, line)) return; // if input fails, exit
        if (line == "1") { // Start game
            round = 1; // Reset round
            turn = 0; // Reset turn
            quitRequested = false; // Reset quit flag
            player = Player(map.getWidth()/2, map.getHeight()-2); // Reset player position and stats 
            enemies.clear(); // Clear enemies
            potion.reset(); // Clear potion
            nextRound(); // Start first round
            gameLoop(); // Enter game loop
        } else if (line == "2") { // Show high scores
            auto top = board.readTop(3); // Read top 3 scores
            std::cout << "Top scores:\n"; // Print header
            for (size_t i=0;i<top.size();++i) { // Print each score with rank
                std::cout << " " << (i+1) << ") " << top[i] << "\n"; // Print score
            }
            if (top.empty()) std::cout << " (no scores yet)\n"; // No scores message
        } else if (line == "3") { // Quit
            return; 
        } else { 
            std::cout << "Please enter 1, 2 or 3.\n"; // Invalid input message
        }
    }
}

void Game::gameLoop() {
    while (!isQuitRequested() && player.isAlive()) { // while not quitting and player alive 
        render(); // render game state
        renderHUD(); // render HUD
        player.takeTurn(*this); // player acts
        if (isQuitRequested() || !player.isAlive()) break; // if quit requested or player dead, break

        // Enemies act
        for (auto &e : enemies) { // for each enemy
            if (e->isAlive()) e->takeTurn(*this); // if enemy is alive, it takes its turn
            if (!player.isAlive()) break; // if player is dead, break
        }
        // Remove dead enemies
        // Lambda in this case is used as a quick way to define a function inline without needing a separate named function.
        // It captures nothing ([]) and takes a const unique_ptr to Enemy and returns true if the enemy is not alive.
        // This essenially rearranges the enemies vector to move all dead enemies to the end and then erases them.
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                    [](const std::unique_ptr<Enemy>& e){ return !e->isAlive(); }), enemies.end());

        // Round clear?
        if (enemies.empty()) { // if no enemies left
            if (round >= 3) { // if round 3 completed
                finishGame(true); // finish game with victory
                return; // if round 3 completed, player wins
            } 
        ++round; // increment round counter
        nextRound(); // else proceed to next round
        continue; 
            }
    }
    if (!player.isAlive()) { //if player died
        finishGame(false); // finish game with defeat
    }
}

void Game::nextRound() { // Method to proceed to the next round
    enemies.clear(); // Clear existing enemies
    spawnEnemiesForRound(); // Spawn enemies for the new round
    placePotionRandom(); // Place a potion randomly on the map
    std::cout << "\n--- Round " << round << " ---\n";// Print round header
}

void Game::render() { 
    // Build a buffer from map
    auto buf = map.data(); // Copy map data into buffer
    // Place potion
    if (potion) buf[potion->y()][potion->x()] = potion->symbol(); // If potion exists, place it on buffer
    // Place enemies
    for (auto &e : enemies) { //for each enemy
        if (e->isAlive()) buf[e->y()][e->x()] = e->symbol(); // if alive, place on buffer
    }
    // Place player last
    buf[player.y()][player.x()] = player.symbol(); // Place player on buffer

    // Print
    for (auto &row : buf) std::cout << row << "\n"; //for each row in buffer, print it
}

void Game::renderHUD() { // Method to render the HUD
    std::cout << "[Round] " << round // Print current round
              << "  [Turn] " << turn // Print current turn
              << "  [Score] " << player.getScore() // Print player score
              << "  [HP] " << player.getHP() << "/" << player.getMaxHP() // Print player HP
              << "  [Potions] " << player.getPotions() // Print player potions
              << "  [Enemies] " << enemies.size() // Print number of enemies
              << "\n";
}

bool Game::moveActor(Actor& a, int dx, int dy) { //Method to move an actor by dx, dy
    int nx = a.x() + dx, ny = a.y() + dy; // Calculate new position
    if (!map.isWalkable(nx, ny)) return false; //if new position not walkable, return false
    // Prevent moving into other actors
    if (isOccupied(nx, ny)) { //if position occupied
        // Attack if player bumps into enemy
        if (&a == &player) { // if actor is player
            if (auto* foe = enemyAt(nx, ny)) { //if enemy at new position
                foe->takeDamage(player.getDamage()); // enemy takes damage
                std::cout << "You hit the " << foe->getName() << " for " << player.getDamage() << ".\n"; // Print hit message
                if (!foe->isAlive()) { // if enemy died
                    std::cout << foe->getName() << " defeated!\n"; // Print defeat message
                    player.addScore(10); // Add score to player
                    onEnemyDefeated(); // Call enemy defeated handler
                }
                return true;
            }
        }
        return false;
    }
    a.setPos(nx, ny); // Move actor to new position
    // Pickup potion
    if (&a == &player) { // if actor is player
        if (auto* pot = potionAt(nx, ny)) { // if potion at new position
            player.addPotion(1); // Add potion to player
            std::cout << "You picked up a potion!\n"; // Print pickup message
            potion.reset(); // Remove potion from game
        }
    }
    return true;
}

bool Game::isOccupied(int x,int y) const { //Method to check if position is occupied
    if (player.x() == x && player.y() == y) return true; //if player is at position, return true
    for (auto &e : enemies) if (e->isAlive() && e->x()==x && e->y()==y) return true; //for each enemy, if alive and at position, return true
    return false; //else return false
}

Enemy* Game::enemyAt(int x,int y) const { //Method to get enemy at position
    for (auto &e : enemies) if (e->isAlive() && e->x()==x && e->y()==y) return e.get(); //for each enemy, if alive and at position, return pointer to enemy
    return nullptr; //else return nullptr
}

void Game::onEnemyDefeated() {
    // If time we can add bnonuses or effects on enemy defeat
}


Potion* Game::potionAt(int x,int y) const { //Method to get potion at position
    if (potion && potion->x()==x && potion->y()==y) return potion.get();  //if potion exists and at position, return pointer to potion
    return nullptr; //else return nullptr
}


void Game::placePotionRandom() { //const Method to place potion randomly on map
    std::uniform_int_distribution<int> dx(1, map.getWidth()-2); // Uniform Integer RNG for x coordinate
    std::uniform_int_distribution<int> dy(1, map.getHeight()-2); // Uniform Integer RNG for y coordinate
    for (int tries=0; tries<200; ++tries) { //for up to 200 tries
        int x = dx(rng), y = dy(rng); // Generate random x,y
        if (!map.isWalkable(x,y)) continue; //if not walkable, continue
        if (isOccupied(x,y)) continue; // if occupied, continue
        if (x==player.x() && y==player.y()) continue; //if player at position, continue
        potion = std::make_unique<Potion>(x,y,9); // Create new potion at position
        return;
    }
    potion.reset(); // If no valid position found, do not place potion
}

void Game::spawnEnemiesForRound() { //Method to spawn enemies for current round
    enemies.clear(); // Clear existing enemies
    // Increasing mobs each round
    int slimes = 1 + round * 2;   // 3,5,7
    int archers = round;          // 1,2,3
    std::uniform_int_distribution<int> dx(1, map.getWidth()-2); // Uniform Integer RNG for x coordinate
    std::uniform_int_distribution<int> dy(1, map.getHeight()-2); // Uniform Integer RNG for y coordinate
    
    auto spawnAt = [&](int count, bool isArcher){ // Lambda thtat captues by reference to spawn, how many enemies, and if they're archers
        int placed = 0; int guard=0; // placed counter and guard to prevent infinite loops
        while (placed < count && guard < 10000) { // while not all placed and under guard limit
            ++guard; // increment guard
            int x = dx(rng), y = dy(rng); // Generate random x,y
            if (!map.isWalkable(x,y)) continue; // if not walkable, continue
            if (isOccupied(x,y)) continue; // if occupied, continue
            // keep some distance from player at spawn
            if (std::abs(x - player.x()) + std::abs(y - player.y()) < 5) continue; //if too close to player, continue
            if (isArcher) enemies.push_back(std::make_unique<Archer>(x,y)); // if archer, spawn archer
            else enemies.push_back(std::make_unique<Slime>(x,y)); // else spawn slime
            ++placed; // increment placed counter
        }
    };
    spawnAt(slimes, false); // Spawn slimes
    spawnAt(archers, true); // Spawn archers
}

void Game::finishGame(bool victory) { // Method to finish the game
    render(); // Render final game state
    renderHUD(); // Render final HUD
    if (victory) { //if victory
        std::cout << "\n*** VICTORY! You cleared all 3 rounds. ***\n"; // Print victory message
        player.addScore(25); // Add victory bonus to score
    } else { //if defeat
        std::cout << "\n*** Defeat. Better luck next time. ***\n"; // Print defeat message
    }
    std::cout << "Final score: " << player.getScore() << "\n"; // Print final score
    try { // Try to record score
        board.recordScore(player.getScore()); // Record score
        auto top = board.readTop(3); // Read top 3 scores
        std::cout << "Top scores:\n"; // Print header
        for (size_t i=0;i<top.size();++i) std::cout << " " << (i+1) << ") " << top[i] << "\n"; // Print each score with rank
    } catch (const std::exception& e) { // Catch any exceptions
        std::cout << "Score save error: " << e.what() << "\n"; // Print error message
    }
}

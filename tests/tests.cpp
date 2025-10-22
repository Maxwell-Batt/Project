
#include "Map.h"
#include "Scoreboard.h"
#include <cassert> // For assert
#include <random> // For std::mt19937
#include <fstream> // For std::ofstream, std::ifstream
#include <cstdio> // For std::remove
#include <iostream>

int main() {
    std::mt19937 rng(42); // Fixed seed for reproducibility
    Map m(10,6,0, rng); // Create empty map 10x6
    // Clear internal walls
    for (int y = 1 ; y < m.getHeight()-1 ; ++y) // for each row except borders
        for (int x = 1 ; x < m.getWidth()-1 ; ++x) // for each column except borders
            if (!m.isWalkable(x,y)) m.setWall(x,y); // if not walkable, set as wall
    // Line of sight straight two tiles
    assert(m.hasLineOfSight(3,3,5,3) == true); // assert is debug check, true if line of sight exists
    // Block the mid tile
    assert(m.isWalkable(4,3)); // Check that (4,3) is walkable
    const_cast<Map&>(m).setWall(4,3); // Set (4,3) as wall using const_cast to modify const object
    assert(m.hasLineOfSight(3,3,5,3) == false); // Now line of sight should be blocked

    // Scoreboard write/read
    const char* fname = "scores_test.txt"; // Test filename
    {
        Scoreboard sb(fname); // Create scoreboard with test filename
        sb.recordScore(10); //  Record score 10
        sb.recordScore(30); // Record score 30
        sb.recordScore(20); // Record score 20
        auto top = sb.readTop(3); // Read top 3 scores
        assert(top.size()==3); // Check size is 3
        assert(top[0]==30 && top[1]==20 && top[2]==10); // Check order of scores
    }
    std::remove(fname); // Clean up test file

    std::cout << "All tests passed.\n"; // If reached here, all assertions passed
    return 0;
}

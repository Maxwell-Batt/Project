
#pragma once
#include <vector>
#include <string>

class Scoreboard {
    std::string filename; // File to store scores
public:
    explicit Scoreboard(std::string fname="scores.txt") // Constructor with default filename
        : filename(std::move(fname)) {} // Initialize filename
    std::vector<int> readTop(int k=3) const; // Read top 3 scores from file
    void recordScore(int s) const; // Record a new score to file
    const std::string& file() const { return filename; } // Getter for filename
};


#include "Scoreboard.h"
#include <fstream> // For file I/O
#include <algorithm> // For std::sort, std::greater
#include <stdexcept> // For std::runtime_error

std::vector<int> Scoreboard::readTop(int k) const { // Read top k scores from file
    std::ifstream in(filename); // Open file for reading
    std::vector<int> scores; // Vector to hold scores
    int s; // Temporary variable for reading scores
    if (in) { // If file opened successfully
        while (in >> s) scores.push_back(s); // while reading scores, add to vector
    }
    std::sort(scores.begin(), scores.end(), std::greater<int>()); // Sort scores in descending order
    if (scores.size() > static_cast<size_t>(k)) scores.resize(k); // Keep only top k scores, where static_cast converts to type T.
    return scores; // Return top scores
}

void Scoreboard::recordScore(int s) const { // Const method to record a new score to file
    // Append; if file missing, create it.
    std::ofstream out(filename, std::ios::app); // Open file in append mode
    if (!out) { // If file couldn't be opened
        throw std::runtime_error("Unable to write to " + filename); // Throw runtime error
    }
    out << s << "\n"; // Write score to file
}

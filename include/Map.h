
#pragma once
#include <vector>
#include <string>
#include <random> // For std::mt19937

class Map {
    int width, height; // Map dimensions
    std::vector<std::string> tiles; // '#' wall, '.' floor
public:
    Map(int w,int h,int obstacleCount, std::mt19937& rng); // Constructor to generate map with obstacles
    int getWidth() const { return width; } // Getter for map width
    int getHeight() const { return height; } // Getter for map height
    bool inBounds(int x,int y) const; // Check if coordinates are within map bounds
    bool isWall(int x,int y) const; // Check if a tile is a wall
    bool isWalkable(int x,int y) const; // Check if a tile is walkable (not a wall)
    const std::vector<std::string>& data() const { return tiles; } // Getter for map data
    bool hasLineOfSight(int x1,int y1,int x2,int y2) const; // straight line Line-of-sight, no walls between
    void setWall(int x,int y); // Set a tile as a wall
};

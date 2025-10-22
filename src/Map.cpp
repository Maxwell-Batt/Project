
#include "Map.h"
#include <algorithm>

Map::Map(int w,int h,int obstacleCount, std::mt19937& rng) : width(w), height(h) { // Constructor to generate map with obstacles
    tiles.assign(height, std::string(width, '.')); // Initialize all tiles as floor ('.')
    // Border walls
    for (int x = 0; x < width ; ++x){ tiles[0][x] = '#'; tiles[height-1][x] = '#'; } // Top and bottom walls intialized with '#'
    for (int y = 0 ; y < height ; ++y){ tiles[y][0] = '#'; tiles[y][width-1] = '#'; } // Left and right walls intialized with '#'
    std::uniform_int_distribution<int> dx(1,width-2); // Uniform int distribution for x coordinates to width-2 to keep within borders
    std::uniform_int_distribution<int> dy(1,height-2); // Uniform int distribution for y coordinates to height-2 to keep within borders
    obstacleCount = std::min(obstacleCount, (width-2)*(height-2)/3); // Limit obstacles to 1/3 of inner area
    int placed = 0; // Count of placed obstacles
    while (placed < obstacleCount) { // While we still need to place obstacles
        int x = dx(rng), y = dy(rng); // Random position within bounds
        if (tiles[y][x] == '.') { tiles[y][x] = '#'; ++placed; } // Place wall if tile is floor
    }
}

bool Map::inBounds(int x,int y) const {
    return x>=0 && x<width && y>=0 && y<height; // Check if coordinates are within map bounds
}

bool Map::isWall(int x,int y) const {
    if (!inBounds(x,y)) return true; // If out of bounds, treat as wall
    return tiles[y][x] == '#';  // Return true if tile is wall
}

bool Map::isWalkable(int x,int y) const { // Check if a tile is walkable (not a wall)
    return inBounds(x,y) && !isWall(x,y); // Return true if in bounds and not a wall
}

void Map::setWall(int x,int y){ // Set a tile as a wall
    if (inBounds(x,y)) tiles[y][x] = '#'; // Set tile to wall if in bounds
}

bool Map::hasLineOfSight(int x1,int y1,int x2,int y2) const { // straight line Line-of-sight, no walls between
    // Archer rule: only straight lines (same row or same column) and exactly distance 2
    if (x1 == x2) { // if same column
        int dy = std::abs(y1 - y2); // initialize vertical distance
        if (dy != 2) return false; // must be exactly 2 tiles apart
        int ymid = (y1 + y2) / 2; // initialize middle y coordinate
        // Ensure the cell between is not a wall
        if (isWall(x1, ymid)) return false; // if wall in between, no line of sight
        return true; // line of sight exists
    } else if (y1 == y2) { // if same row
        int dx = std::abs(x1 - x2); // initialize horizontal distance
        if (dx != 2) return false; // must be exactly 2 tiles apart
        int xmid = (x1 + x2) / 2; // initialize middle x coordinate 
        if (isWall(xmid, y1)) return false; // if wall in between, no line of sight
        return true; // line of sight exists
    }
    return false; // not aligned, no line of sight
}

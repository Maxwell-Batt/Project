
#pragma once
#include <string>
#include <utility> // For std::move

struct Vec2 { int x; int y; }; // Simple 2D vector struct

class Game;

class GameObject {
protected:
    Vec2 pos; // Position of the object
    char glyph; // Character representation, glyph respresenting symbol object on screen
    std::string name; // Name of the object
public:
    GameObject(int x, int y, char g, std::string n)
    : pos{ x, y }, glyph(g), name(std::move(n)) {} // Initializer list to set position, glyph, and name
    virtual ~GameObject() = default; // Virtual destructor for cleanup in derived classes to prevent memory leaks.

    int x() const { return pos.x; } // Getter for x position
    int y() const { return pos.y; } // Getter for y position
    void setPos(int nx, int ny) { pos.x = nx; pos.y = ny; } // Setter for position

    char symbol() const { return glyph; } // Getter for glyph symbol
    const std::string& getName() const { return name; } // Getter for name

    // Not all objects act each turn for example a Potion
    virtual void takeTurn(Game&) {} // Virtual function for taking a turn, default does nothing
};

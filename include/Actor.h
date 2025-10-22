
#pragma once // Used insead of indlude guards to prevent multiple inclusions
#include "GameObject.h" // Include the base class header
#include <algorithm> // For std::min

// Base class GameObject with Subclass Actor, example of Inheritance
class Actor : public GameObject {
protected:
    // Protected because we may want derived classes to access these directly
    int hp; // Current health points
    int maxHp; // Maximum health points
    int damage;  // Damage this actor can inflict
public:
   
    // Iniitializer list to set up base GameObject and Actor specific attributes
    Actor(int x,int y,char g,std::string n,int hp_,int dmg)
    : GameObject(x,y,g,std::move(n)), hp(hp_), maxHp(hp_), damage(dmg) {} 

    int getHP() const { return hp; } // Getter for current HP
    int getMaxHP() const { return maxHp; } // Getter for maximum HP
    int getDamage() const { return damage; } // Getter for damage
    bool isAlive() const { return hp > 0; } // Check if actor is alive
    void heal(int amt) { hp = std::min(maxHp, hp + amt); } // Heal actor
    void takeDamage(int amt) { hp -= amt; if (hp < 0) hp = 0; } // Inflict damage
};

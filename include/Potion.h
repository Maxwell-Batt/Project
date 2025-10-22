
#pragma once
#include "GameObject.h"

class Potion : public GameObject {
    int healAmount; // Amount of healing provided by the potion
public:
    // Iniitializer list to set up base GameObject attributes
    Potion(int x,int y,int heal=9) : GameObject(x,y,'!',"Potion"), healAmount(heal) {}
    int heal() const { return healAmount; } // Getter for heal amount
};

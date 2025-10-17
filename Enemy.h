// class for enemies

#ifndef ENEMY
#define ENEMY

#include "Character.h"

class Enemy : public Character {

    private:

    int cooldown;
    bool isReady;

    public:

    // constructors

    Enemy();

    // getter setter functions

    void setCooldown(int cooldown);
    int getCooldown();
    void setIsReady(bool isReady);
    bool getIsReady();
};

#endif
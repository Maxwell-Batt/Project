// class file for controller class

#ifndef GAMECONTROLLER
#define GAMECONTROLLER

#include "gameObject.h"

class Controller {
    private::
    int gameState;
    int numEntities = 0;
    gameObject** gameObjects;
    public:
    Controller();
    void setgameState(int gameState);
    void setnumEntities(int numEntities);

};

#endif
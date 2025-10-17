// class for controller class

#ifndef GAMECONTROLLER
#define GAMECONTROLLER

#include "GameObject.h"

class Controller {
    private:
    int gameState;
    int numEntities;
    GameObject** gameObjects;
    int score;
    public:
    Controller();
    void setgameState(int gameState);
    int getGameState();
    void setnumEntities(int numEntities);
    int getNumEntities();
    void setScore(int score);
    int getScore();
    void gameStart();
    void gameEnd();
    void drawMap();
    void levelStart(int levelNum);
    // void levelEnd();

};

#endif
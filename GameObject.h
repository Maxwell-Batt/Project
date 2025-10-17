// class for game objects
#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <string>
using namespace std;

class GameObject {
    private:
    int xPosition;
    int yPosition;
    int ID;
    string name;

    public:
    GameObject();
    GameObject(int xPosition, int yPosition, int ID, string name);
    void setxPosition(int x);
    int getxPosition();
    void setyPosition(int y);
    int getyPosition();
    void setID(int ID);
    int getID();
    void setName(string name);
    string getName();
};

#endif
// class for game objects
#ifndef GAMEOBJECT
#define GAMEOBJECT

class gameObject {
    private:
    int xPosition;
    int yPosition;
    int ID;

    public:
    gameObject()
    void setxPosition(int x);
    void seyyPosition(int y);
    void setID(int ID);
    int getxPosition();
    int getyPosition();
    int getID();
};

#endif
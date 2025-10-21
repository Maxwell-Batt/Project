#include <iostream>
 using namespace std;


 int main(){

    int rockx = 3;
    int rocky = 3;
    int playerx = 2;
    int playery = 1;
    int slimex = 4;
    int slimey = 5;

    for (int i=1; i<6; i++){
        for(int j=1; j<6; j++){
            int tile;
            if(i==rocky && j==rockx){
                tile = 3;
            }
            else if(i==playery && j==playerx){
                tile = 1;
            }
            else if(i==slimey && j==slimex){
                tile = 2;
            }
            else{
                tile = 0;
            }
            switch(tile){
                case 0:
                cout << " |";
                break;
                case 1:
                cout << "P|";
                break;
                case 2:
                cout << "S|";
                break;
                case 3:
                cout << "R|";
                break;
            }
        }
        cout << "|" << endl;
    }

    return 0;
 }
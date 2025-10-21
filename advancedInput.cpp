#include <iostream>
#include <ncurses.h>

int main() {
    initscr(); // Initialize ncurses
    cbreak();  // Disable line buffering
    noecho();  // Disable echoing

    int rockx = 3;
    int rocky = 3;
    int playerx = 2;
    int playery = 1;
    int slimex = 4;
    int slimey = 5;
    
    char key = 'h';
    while(key != 'q'){
    // printw("Press a key (without Enter): ");
    key = getch(); // Read a single character
    clear();
    printw("\nYou pressed: %c\n", key);
    refresh(); // Update the screen

    if(key == 'w'){
        playery--;
    }
    else if(key == 's'){
        playery++;
    }
    else if(key == 'd'){
        playerx++;
    }
    else if(key == 'a'){
        playerx--;
    }

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
                printw(" |");
                break;
                case 1:
                printw("P|");
                break;
                case 2:
                printw("S|");
                break;
                case 3:
                printw("R|");
                break;
            }
        }
        printw("\n");
    }
    
}
    endwin(); // End curses mode
    return 0;
}  

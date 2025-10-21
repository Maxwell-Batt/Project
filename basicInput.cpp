#include <iostream>
#include <ncurses.h>

int main() {
    initscr(); // Initialize ncurses
    cbreak();  // Disable line buffering
    noecho();  // Disable echoing
    
    char key = 'h';
    while(key != 'q'){
        printw("Press a key (without Enter): ");
        key = getch(); // Read a single character
        printw("\nYou pressed: %c\n", key);
        refresh(); // Update the screen
}
    endwin(); // End curses mode
    return 0;
}
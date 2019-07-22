#include <iostream> // a prerequisite library for ncurses.h
#include <ncurses.h>
#include <unistd.h> // to use usleep() function



/* Note:
 * When compile, one needs to ADD "-lncurses" in the end,
 * so as to dynamically link the library ncurses.h to this program
 * For example: g++ test_Ncurses_library.cpp -lncurses 
 **/

WINDOW* create_new_window(int height, int width, int start_y, int start_x);

int main() {

    // sleep for 1000 ms
    usleep(1000);

    // init the ncurses
    initscr();

    // Use noecho() for unwanted characters
    noecho();

    // an equivalent to:
    // std::cout << "HELLO!";
    addch('H' | A_UNDERLINE);
    addch('E' | A_UNDERLINE);
    addch('L' | A_BOLD);
    addch('L' | A_BOLD);
    addch('O');
    addch('!');

    // a wait: that the computer would wait until you give it an input
    // function which reads input characters from keyboard
    getch();

    // release the window    
    endwin();

    return 0;
}
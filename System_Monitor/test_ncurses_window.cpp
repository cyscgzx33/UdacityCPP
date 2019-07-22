#include <ncurses.h>

int main() {
    initscr();
    // it can display multiple windows, BUT at least without overlap
    WINDOW *win = newwin(20, 20, 0, 0);
    box(win, '|', '-'); // pass them, what we want to draw with lines and columns
    
    /* refresh data  */
    // so that inserted data can be correctly shown in the window
    refresh();
    wrefresh(win);
    
    getch(); // get ch from keyboard, so the program pauses instead of just vanishing
    endwin();
    delwin(win); // delete obj win to avoid memory leaks

    return 0;
}
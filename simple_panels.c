#include <panel.h>

#define SIZE 3
int height = 10, width = 30, row = 2, col = 10;

int
main(void)
{
    int i;
    WINDOW *wins[SIZE];
    PANEL *panels[SIZE];

    initscr();

    for(i = 0; i < SIZE; ++i){
        wins[i] = newwin(height, width, row+(i*3), col+(i*5));
        box(wins[i], 0, 0);
        panels[i] = new_panel(wins[i]);
    }
    update_panels();
    doupdate();

    getch();
    endwin();
    return 0;
}
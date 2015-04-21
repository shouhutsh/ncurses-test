#include <stdlib.h>
#include <ncurses.h>

int
main(void)
{
    initscr();
    printw("Hello");
    refresh();
    getch();
    def_prog_mode();

    endwin();
    system("/bin/sh");
    reset_prog_mode();

    printw(" world");
    getch();
    refresh();

    endwin();
    return 0;
}
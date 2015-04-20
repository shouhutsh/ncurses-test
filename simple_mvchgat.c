#include <ncurses.h>

int
main(void)
{
    initscr();
    start_color();

    init_pair(1, COLOR_RED, COLOR_YELLOW);
    printw("hello, this is a test!");

    refresh();
    getch();

    mvchgat(0, 0, -1, A_BOLD, 1, NULL);

    refresh();
    getch();
    endwin();
    return 0;
}
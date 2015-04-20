#include <string.h>
#include <ncurses.h>

int
main(void)
{
    char msg[] = "hello, world!";
    int row, col;

    initscr();
    getmaxyx(stdscr, row, col);
    mvprintw(row/2, (col-strlen(msg))/2, "%s", msg);

    mvprintw(row-2, 0, "this screen has %d rows and %d cols\n", row, col);
    printw("GoodBye!");

    //refresh();
    getch();
    endwin();
    return 0;
}
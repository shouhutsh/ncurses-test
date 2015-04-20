#include <ncurses.h>
#include <string.h>

int
main(void)
{
    char msg[] = "Enter a string: ";

    char buf[BUFSIZ] = {0};
    int row, col;

    initscr();
    getmaxyx(stdscr, row, col);

    mvprintw(row/2, (col-strlen(msg))/2, "%s", msg);
    getstr(buf);
    mvprintw(row-2, 0, "You enter string is: %s\n", buf);

    //refresh();
    getch();
    endwin();
    return 0;
}
#include <string.h>
#include <ncurses.h>

void
print_in_middle(WINDOW * win, int starty, int startx, int width, char *string){
    int len, row, col;
    if(NULL == win) win = stdscr;
    getyx(win, row, col);

    if(0 != starty) row = starty;
    if(0 != startx) col = startx;
    if(0 == width) width = 80;
    len = strlen(string);

    col = startx + (width-len)/2;
    mvwprintw(win, row, col, "%s", string);
    wrefresh(win);
}

int
main(void)
{
    initscr();
    if(! has_colors()){
        endwin();
        printf("Your screen mot support color!\n");
        return 1;
    }
    start_color();

    init_pair(1, COLOR_RED, COLOR_YELLOW);

    attron(COLOR_PAIR(1));
    print_in_middle(stdscr, 0, 0, 0, "hello, in color!");
    attroff(COLOR_PAIR(1));

    if(can_change_color()){
        init_color(COLOR_RED, 500, 0, 0);
        attron(COLOR_PAIR(1));
        print_in_middle(stdscr, 1, 0, 0, "hello, in color!");
        attroff(COLOR_PAIR(1));
    }

    getch();
    endwin();
    return 0;
}
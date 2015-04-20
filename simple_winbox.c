#include <ncurses.h>

#define DEF_CHAR ' '

WINDOW * create_win(int height, int width, int starty, int startx)
{
    WINDOW * win;
    win = newwin(height, width, starty, startx);
    //box(win, 0, 0);
    wborder(win, '|', '|', '-', '-', '*', '+', '+', '*');
    wrefresh(win);
    return win;
}

void destroy_win(WINDOW * win)
{
    wborder(win, DEF_CHAR, DEF_CHAR, DEF_CHAR, DEF_CHAR, DEF_CHAR, DEF_CHAR, DEF_CHAR, DEF_CHAR);
    wrefresh(win);
    delwin(win);
}

int
main(void)
{
    int ch;
    WINDOW * win;
    int height = 3, width = 10, starty, startx;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    starty = (LINES - height)/2;
    startx = (COLS - width)/2;
    printw("Press <Enter> to exit");
    refresh();

    win = create_win(height, width, starty, startx);
    while('\n' != (ch = getch())){
        switch(ch){
            case KEY_LEFT:
                destroy_win(win);
                win = create_win(height, width, starty, --startx);
                break;
            case KEY_RIGHT:
                destroy_win(win);
                win = create_win(height, width, starty, ++startx);
                break;
            case KEY_UP:
                destroy_win(win);
                win = create_win(height, width, --starty, startx);
                break;
            case KEY_DOWN:
                destroy_win(win);
                win = create_win(height, width, ++starty, startx);
                break;
        }
    }
    endwin();
    return 0;
}
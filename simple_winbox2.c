#include <ncurses.h>

typedef struct {
    int starty, startx,
        height, width;
    struct WIN_BORDER {
        chtype l, r, u, d,
            lu, ru, ld, rd;
    }border;
}WIN;

const WIN * init_win(WIN * win){
    win->height = 3;
    win->width = 10;
    win->starty = (LINES - win->height)/2;
    win->startx = (COLS - win->width)/2;
    win->border.l = '|';
    win->border.r = '|';
    win->border.u = '-';
    win->border.d = '-';
    win->border.lu = '+';
    win->border.ru = '*';
    win->border.ld = '+';
    win->border.rd = '*';
    return win;
}

void print_win(const WIN * win){
    mvprintw(1, 0, "y:%d x:%d h:%d w:%d", win->starty, win->startx, win->height, win->width);
    refresh();
}

const WIN * create_box(const WIN * win, int show_border){
    int i, j;
    int y, x, h, w;
    y = win->starty;
    x = win->startx;
    h = win->height;
    w = win->width;

    if(TRUE == show_border){
        mvaddch(y, x, win->border.lu);
        mvaddch(y+h, x, win->border.ru);
        mvaddch(y, x+w, win->border.ld);
        mvaddch(y+h, x+w, win->border.ru);

        mvvline(y+1, x, win->border.l, h-1);
        mvvline(y+1, x+w, win->border.r, h-1);
        mvhline(y, x+1, win->border.u, w-1);
        mvhline(y+h, x+1, win->border.d, w-1);
    }else{
        for(i = y; i <= y+h; ++i){
            for(j = x; j <= x+w; ++j){
                mvaddch(i, j, ' ');
            }
        }
    }

    refresh();
    return win;
}

int
main(void)
{
    int ch;
    WIN win;

    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    init_pair(1, COLOR_RED, COLOR_YELLOW);
    init_win(&win);

    attron(COLOR_PAIR(1));
    printw("Press F1 to exit");
    refresh();
    attroff(COLOR_PAIR(1));

    print_win(create_box(&win, TRUE));
    while('\n' != (ch = getch())){
        switch(ch){
            case KEY_LEFT:
                print_win(create_box(&win, FALSE));
                --win.startx;
                print_win(create_box(&win, TRUE));
                break;
            case KEY_RIGHT:
                print_win(create_box(&win, FALSE));
                ++win.startx;
                print_win(create_box(&win, TRUE));
                break;
            case KEY_UP:
                print_win(create_box(&win, FALSE));
                --win.starty;
                print_win(create_box(&win, TRUE));
                break;
            case KEY_DOWN:
                print_win(create_box(&win, FALSE));
                ++win.starty;
                print_win(create_box(&win, TRUE));
                break;
        }
    }

    endwin();
    return 0;
}
#include <panel.h>
#include <string.h>

#define SIZE 3

int color_pair[SIZE+1];
int height = 10, width = 40, row = 2, col = 10;

void init_panels(PANEL ** panels, int n);
void update_win(WINDOW * win, const char *label, int color);
void print_in_middle(WINDOW * win, int starty, int startx, int width, const char *str, chtype color);

void
init_panels(PANEL ** panels, int n){
    int i;
    char buf[80] = {0};
    WINDOW * win;
    for(i = 0; i < n; ++i){
        win = newwin(height, width, row+i*3, col+i*5);
        sprintf(buf, "this is %d panel.", i);
        update_win(win, buf, color_pair[i%SIZE]);
        panels[i] = new_panel(win);
    }
}

void
update_win(WINDOW * win, const char *label, int color){
    int h, w;
    getmaxyx(win, h, w);

    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwaddch(win, 2, w-1, ACS_RTEE);
    mvwhline(win, 2, 1, ACS_HLINE, w-2);

    print_in_middle(win, 1, 0, w, label, COLOR_PAIR(color));
}

void
print_in_middle(WINDOW * win, int starty, int startx, int width, const char *str, chtype color){
    int x, y;
    getyx(win, y, x);

    if(NULL == win) win = stdscr;
    if(0 != starty) y = starty;
    if(0 != startx) x = startx;
    if(0 == width) width = 80;

    x = startx + (width-strlen(str))/2;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", str);
    wattroff(win, color);
}

void
init_color_pair(){
    int i;
    for(i = 0; i < SIZE+1; ++i){
        init_pair(i+1, (i+1)%7, (i+2)%7);
        color_pair[i] = i;
    }
}

int
main(void)
{
    int i;
    WINDOW * wins[SIZE];
    PANEL * top, * panels[SIZE];

    initscr();
    start_color();

    init_color_pair();
    init_panels(panels, SIZE);
    for(i = 0; i < SIZE; ++i){
        set_panel_userptr(panels[i], panels[(i+1)%SIZE]);
    }
    update_panels();
    doupdate();

    attron(COLOR_PAIR(SIZE+1));
    printw("Press <Tab> to change window.\n");
    printw("Press <Enter> to exit.\n");
    attroff(COLOR_PAIR(SIZE+1));

    top = panels[SIZE-1];
    while('\n' != (i = getch())){
        if('\t' == i){
            top = panel_userptr(top);
            top_panel(top);
            update_panels();
            doupdate();
        }
    }
    endwin();
    return 0;
}
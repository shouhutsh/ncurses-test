#include <panel.h>
#include <string.h>

#define SIZE 3

int color_pair[SIZE+1];
int height = 10, width = 40, row = 5, col = 20;

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
        // FIXME
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

void
do_move(PANEL * panel, int key){
    switch(key){
        case 'h': --col; break;
        case 'l': ++col; break;
        case 'k': --row; break;
        case 'j': ++row; break;
        default:
            return;
    }
    // TODO
}

void
do_change(PANEL * panel, int key){
    switch(key){
        case 'h': --width; break;
        case 'l': ++width; break;
        case 'k': --height; break;
        case 'j': ++height; break;
        default:
            return;
    }
    // TODO
}

void
do_use(PANEL * panel){
    WINDOW * old_win = panel_window(panel);
    WINDOW * new_win = newwin(height, width, row, col);
    update_win(new_win, "new window", 1);
    replace_panel(panel, new_win);
    delwin(old_win);
}

void
init_panel_place(const PANEL * panel){
    getbegyx(panel_window(panel), row, col);
    getmaxyx(panel_window(panel), height, width);
}

int
main(void)
{
    PANEL * top, * panels[SIZE];
    int i, move_mode = FALSE, change_mode = FALSE;

    initscr();
    start_color();
    noecho();

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
    mvprintw(LINES-4, 0, "Press 'kjhl' to move the window.\n");
    mvprintw(LINES-3, 0, "Press 'u' to use the change.\n");
    mvprintw(LINES-2, 0, "Press 'm' to set move_mode.\n");
    mvprintw(LINES-1, 0, "Press 'c' to set change_mode.");
    attroff(COLOR_PAIR(SIZE+1));
    refresh();

    top = panels[SIZE-1];
    init_panel_place(top);
    while('\n' != (i = getch())){
        switch(i){
            case '\t':
                top = panel_userptr(top);
                top_panel(top);
                init_panel_place(top);
                update_panels();
                doupdate();
                break;
            case 'c':
                change_mode = TRUE;
                break;
            case 'm':
                move_mode = TRUE;
                break;
            case 'u':
                if(change_mode || move_mode){
                    do_use(top);
                    change_mode = FALSE;
                    move_mode = FALSE;
                    update_panels();
                    doupdate();
                }
                break;

            case 'h':
            case 'l':
            case 'k':
            case 'j':
                if(change_mode){
                    do_change(top, i);
                }else if(move_mode){
                    do_move(top, i);
                }
                break;

            default:
                mvprintw(3, 0, "you pressed character is '%c'", i);
                refresh();
        }
    }
    endwin();
    return 0;
}
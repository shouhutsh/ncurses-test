#include <ncurses.h>

char *choices[] = {
    "choice 1",
    "choice 2",
    "choice 3",
    "choice 4",
    "Exit"
};

int row, col;
int count = sizeof(choices) / sizeof(char *);
#define EXIT count-1
#define HEIGHT 10
#define WIDTH  30
#define OFF_SIZE 2

void
print_menu(WINDOW * win, const int choose){
    int i, y = OFF_SIZE, x = OFF_SIZE;
    box(win, 0, 0);
    for(i = 0; i < count; ++i){
        if(choose == i){
            wattron(win, A_REVERSE);
            mvwprintw(win, y, x, "%s", choices[i]);
            wattroff(win, A_REVERSE);
        }else{
            mvwprintw(win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(win);
}

int
report_choice(const MEVENT * event){
    int i, x = event->x, y = event->y;

    for(i = 0; i < count; ++i){
        if(row+OFF_SIZE + i == y && (x > col+OFF_SIZE && x <= col+OFF_SIZE + strlen(choices[i]))){
            return i;
        }
    }
    return -1;
}

int
main(void)
{
    MEVENT event;
    WINDOW * menu;
    int ch, choice = 0;
    initscr();
    noecho();
    cbreak();
    mousemask(ALL_MOUSE_EVENTS, NULL);

    row = (LINES - HEIGHT)/2;
    col = (COLS - WIDTH)/2;

    menu = newwin(HEIGHT, WIDTH, row, col);
    keypad(menu, TRUE);

    mvprintw(0, 0, "Click <Enter> to exit");
    // 没有这个的话不会显示窗口
    refresh();
    print_menu(menu, choice);

    while(1){
        ch = wgetch(menu);
        switch(ch){
            case KEY_MOUSE:
                if(OK == getmouse(&event)){
                    mvprintw(2, 0, "Mouse(%d): made is 0x%X, x=%d y=%d z=%d", event.id, event.bstate, event.x, event.y, event.z);
                    refresh();
                    if(event.bstate&BUTTON1_CLICKED){
                        if(EXIT == (choice = report_choice(&event))){
                            goto exit;
                        }
                    }
                }
                break;
            case KEY_UP:
                if(0 != choice){
                    --choice;
                }
                break;
            case KEY_DOWN:
                if(count != choice){
                    ++choice;
                }
                break;
            default:
                mvprintw(LINES-2, 0, "Charcter pressed is %3d, It can printed ad '%c'", ch, ch);
                refresh();
        }
        print_menu(menu, choice);
        if('\n' == ch && EXIT == choice){
            break;
        }
    }
exit:
    endwin();
    return 0;
}
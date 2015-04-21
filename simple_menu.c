#include <ncurses.h>

char *choices[] = {
    "choice 1",
    "choice 2",
    "choice 3",
    "choice 4",
    "Exit"
};
int count = sizeof(choices) / sizeof(char *);
#define EXIT count-1

void
print_menu(WINDOW * win, const int choose){
    int i, y = 2, x = 2;
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

#define HEIGHT 10
#define WIDTH  30

int
main(void)
{
    WINDOW * menu;
    int row, col;
    int ch, choice = 0;
    initscr();
    noecho();
    cbreak();

    row = (LINES - HEIGHT)/2;
    col = (COLS - WIDTH)/2;

    printw("row:%d col:%d", row, col);
    menu = newwin(HEIGHT, WIDTH, row, col);
    keypad(menu, TRUE);

    mvprintw(0, 0, "Press <Enter> to exit");
    // 没有这个的话不会显示窗口
    refresh();
    print_menu(menu, choice);

    while(ch = wgetch(menu)){
        if('\n' == ch && EXIT == choice){
            break;
        }
        switch(ch){
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
    }

    endwin();
    return 0;
}
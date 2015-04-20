#include <ncurses.h>

int
main(void)
{
    int ch;
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    ch = getch();
    while(1){
        if(KEY_F(1) == ch){
            printw("F1 key pressed");
        }else if('\n' == ch){
            break;
        }else{
            printw("You pressed is :");
            attron(A_BOLD);
            printw("%c", ch);
            attroff(A_BOLD);
        }

        refresh();
        ch = getch();
    }

    endwin();
    return 0;
}
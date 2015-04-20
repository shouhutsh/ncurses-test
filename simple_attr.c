#include <stdlib.h>
#include <ncurses.h>

int
main(int argc, char *argv[])
{
    FILE *fp;
    int goto_prev = FALSE, prev = EOF, ch;
    if(2 != argc){
        printf("Usage: %s <a c file name>\n", argv[0]);
        exit(1);
    }
    if((fp = fopen(argv[1], "r")) == NULL){
        printf("Open %s error!\n", argv[1]);
        exit(1);
    }

    initscr();
    while((ch = fgetc(fp)) != EOF){
        if('/' == prev && '*' == ch){
            attron(A_REVERSE | A_BLINK);
            goto_prev = TRUE;
        }
        if(TRUE == goto_prev){
            int row, col;
            getyx(stdscr, row, col);
            mvprintw(row, col-1, "%c%c", prev, ch);
            goto_prev = FALSE;
        }else{
            printw("%c", ch);
        }
        if('*' == prev && '/' == ch){
            attroff(A_REVERSE | A_BLINK);
            goto_prev = TRUE;
        }
        prev = ch;
    }

    refresh();
    getch();
    endwin();
    return 0;
}
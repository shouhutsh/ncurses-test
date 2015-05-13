#include <form.h>

int main(void)
{
    FIELD *field[3];
    FORM *my_form;
    int ch;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    field[0] = new_field(1, 20, 4, 18, 0, 0);
    field[1] = new_field(1, 10, 6, 18, 0, 0);
    field[2] = NULL;

    set_field_fore(field[0], COLOR_PAIR(1));
    set_field_back(field[0], COLOR_PAIR(1) | A_UNDERLINE);
    field_opts_off(field[0], O_AUTOSKIP);

    set_field_just(field[0], JUSTIFY_LEFT);
    //set_field_buffer(field[0], 0, "input your name");
    //field_opts_on(field[0], O_BLANK);

    field_opts_off(field[0], O_STATIC);
    set_max_field(field[0], 50);

    set_field_back(field[1], A_UNDERLINE);
    field_opts_off(field[1], O_PUBLIC | O_AUTOSKIP);

    my_form = new_form(field);
    post_form(my_form);
    refresh();

    set_current_field(my_form, field[0]);
    mvprintw(4, 9, "username:");
    mvprintw(6, 9, "password:");
    refresh();

    while('\n' != (ch = getch())){
        switch(ch){
            case KEY_DOWN:
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_UP:
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_LEFT:
                form_driver(my_form, REQ_PREV_CHAR);
                break;
            case KEY_RIGHT:
                form_driver(my_form, REQ_NEXT_CHAR);
                break;
            case KEY_BACKSPACE:
                form_driver(my_form, REQ_DEL_PREV);
                break;
            case KEY_DC:
                form_driver(my_form, REQ_DEL_CHAR);
                break;
            default:
                form_driver(my_form, ch);
                break;
        }
    }

    form_driver(my_form, REQ_VALIDATION);
    mvprintw(10, 10, "username: %s", field_buffer(field[0], 0));
    mvprintw(11, 10, "password: %s", field_buffer(field[1], 0));
    refresh();
    getch();

    unpost_form(my_form);
    free_form(my_form);
    free_field(field[0]);
    free_field(field[1]);
    endwin();
    return 0;
}
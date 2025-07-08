#include <ncurses.h>
#include "../include/cli.hpp"

void init_cli() {
    initscr();
    printw("Linux Process Monitor\n");
    refresh();
}

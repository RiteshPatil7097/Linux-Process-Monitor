#include <thread>
#include <chrono>
#include <ncurses.h> 
#include "../include/monitor.hpp"
#include "../include/parser.hpp"

void start_monitor() {
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    nodelay(stdscr, TRUE);  // Don't block on getch()
    keypad(stdscr, TRUE);   // Enable special keys

    while (true) {
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;  // exit the monitor if q is pressed
        }

        auto processes = parse_proc();

        mvprintw(0, 0, "%-6s | %-20s | %-8s | %-8s", "PID", "Name", "CPU (%)", "MEM (MB)");
        mvprintw(1, 0, "----------------------------------------------------------");

        int row = 2;
        for (const auto& p : processes) {
            mvprintw(row++, 0, "%-6d | %-20s | %-8.2f | %-8.2f", p.pid, p.name.c_str(), p.cpu, p.memory);
        }

        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        clear();
    }

    endwin();  // Close ncurses mode
}

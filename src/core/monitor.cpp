#include <thread>
#include <chrono>
#include <ncurses.h> 
#include "../include/monitor.hpp"
#include "../include/parser.hpp"

void start_monitor() {
    initscr();              
    cbreak();               
    noecho();               
    nodelay(stdscr, TRUE);  
    keypad(stdscr, TRUE);   

    while (true) {
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;  
        }

        auto processes = parse_proc();

        
        mvprintw(0, 0, "%-6s | %-20s | %-8s | %-8s | %-10s | %-s", 
                 "PID", "Name", "CPU (%)", "MEM (MB)", "Time(s)", "Path");
        mvprintw(1, 0, "--------------------------------------------------------------------------------------------");

        int row = 2;
        for (const auto& p : processes) {
           
            mvprintw(row++, 0, "%-6d | %-20s | %-8.2f | %-8.2f | %-10.2f | %-s", 
                     p.pid, p.name.c_str(), p.cpu, p.memory, p.time, p.path.c_str());
        }

        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        clear();
    }

    endwin(); 
}

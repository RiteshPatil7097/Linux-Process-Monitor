#include <thread>
#include <chrono>
#include <ncurses.h> 
#include "../include/monitor.hpp"
#include "../include/parser.hpp"

void start_monitor() {
    while (true) {
        auto processes = parse_proc();
        for (const auto& p : processes) {
            printw("PID: %d | Name: %s | CPU: %.2f | MEM: %.2f\n", p.pid, p.name.c_str(), p.cpu, p.memory);
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        clear();
    }
}

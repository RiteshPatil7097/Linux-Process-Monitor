#include <iostream>
#include <ncurses.h>
#include "../include/cli.hpp"
#include "../include/monitor.hpp"

int main() {
    int choice;
nodelay(stdscr, TRUE);
    while (true) {
         int ch = getch();
    if (ch == 'q' || ch == 'Q') {
        break;  
    }

        std::cout << "\n--- Linux Process Manager ---\n";
        std::cout << "1. Monitor Processes\n";
        std::cout << "2. Control Process (Kill / Suspend / Resume)\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                init_cli();      
                start_monitor(); 
                endwin();         
                break;
            case 2:
                handle_process_control();
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}

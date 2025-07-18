#include "../include/cli.hpp"
#include "../include/monitor.hpp"
#include <iostream>

int main() {
    while (true) {
        std::cout << "\n1. Monitor Processes\n"
                  << "2. Control Process (Kill/Suspend/...)\n"
                  << "0. Exit\n"
                  << "Enter choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                start_monitor();
                break;
            case 2:
                handle_process_control();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid option\n";
        }
    }

    return 0;
}









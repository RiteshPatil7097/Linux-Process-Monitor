#include <ncurses.h> 
#include "../include/cli.hpp" 
#include "../include/process_control.hpp" 
 
#include <iostream> 
 
 
void init_cli() { 
    initscr(); 
    printw("Linux Process Monitor\n"); 
    refresh(); 
} 
 
void handle_process_control() { 
    int pid; 
    std::cout << "Enter PID: "; 
    std::cin >> pid; 
 
    std::cout << "Choose Action:\n" 
              << "1. Kill\n" 
              << "2. Terminate\n" 
              << "3. Suspend\n" 
              << "4. Resume\n" 
              << "Choice: "; 
    int choice; 
    std::cin >> choice; 
 
    ProcessAction action; 
    switch (choice) { 
        case 1: action = ProcessAction::KILL; break; 
        case 2: action = ProcessAction::TERMINATE; break; 
        case 3: action = ProcessAction::SUSPEND; break; 
        case 4: action = ProcessAction::RESUME; break; 
        default: std::cout << "Invalid option.\n"; return; 
    } 
 
    if (control_process(pid, action)) { 
        std::cout << "Action successful on PID " << pid << "\n"; 
    } else { 
        perror("Failed"); 
    } 
}
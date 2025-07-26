#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

struct ProcessInfo {
    int pid;
    std::string name;
    double cpu;
    double memory;
    // Israr - Added time and path for future use
    double time;        
    std::string path; 
};

std::vector<ProcessInfo> parse_proc();

#endif
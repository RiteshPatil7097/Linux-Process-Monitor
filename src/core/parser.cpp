#include "../include/parser.hpp"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <cstring>

std::vector<ProcessInfo> parse_proc() {
    std::vector<ProcessInfo> result;
    DIR* dir = opendir("/proc");
    if (!dir) return result;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            int pid = atoi(entry->d_name);
            if (pid <= 0) continue;

            std::string statPath = "/proc/" + std::string(entry->d_name) + "/stat";
            std::ifstream statFile(statPath);
            if (!statFile.is_open()) continue;

            std::string line;
            getline(statFile, line);
            std::istringstream iss(line);
            std::string name;
            ProcessInfo p;
            p.pid = pid;
            iss >> pid >> name;
            p.name = name;
            p.cpu = 0.0;      // Placeholder
            p.memory = 0.0;   // Placeholder
            result.push_back(p);
        }
    }
    closedir(dir);
    return result;
}
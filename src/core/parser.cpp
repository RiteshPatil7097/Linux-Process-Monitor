#include "../include/parser.hpp"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <cstring>

std::vector<ProcessInfo> parse_proc() {
    std::vector<ProcessInfo> result;
    DIR* dir = opendir("/proc");
    if (!dir) return result;

    // Israr - block for getting Uptime
    double uptime = 0.0;
    { 
        std::ifstream temp_file("/proc/uptime");
        if( temp_file.is_open() ) temp_file >> uptime;
    }
    auto  hertz = sysconf(_SC_CLK_TCK);
    // End of Israr's block

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
            
            // Commented because its hardCoded
            // iss >> pid >> name;

            // p.name = name;
            // p.cpu = 0.0;      // Placeholder
            // p.memory = 0.0;   // Placeholder

            std::string comm,dummy;
            char state;
            unsigned long user_time, sys_time,start_time;
            iss.clear();
            iss.seekg(0);
            iss >> pid >> comm >> state;


            for(int i=0; i<10; i++) iss >> dummy; // uptime
            iss >> user_time >> sys_time; 

            for(int i=0; i<4; i++) iss >> dummy; // start_time
            iss >> start_time;
            
            if (!comm.empty() && comm.front() == '(' && comm.back() == ')') {
                comm = comm.substr(1, comm.size() - 2);
            }
            p.name = comm;
            auto total_time = user_time + sys_time;
            // it not works then try to multiply by doing uptime * hertz - start_time / hertz;
            auto second = uptime - (start_time / (double)hertz);
            p.cpu = (second > 0) ? (100.0 * ((total_time / (double)hertz) / second)) : 0.0;
            
            auto statusPath = "/proc/" + std::to_string(pid) + "/status";
            std::ifstream statusFile(statusPath);
            p.memory = 0.0;
            if( statusFile.is_open()) {
                std::string memLine;
                while( getline(statusFile,memLine)){
                     if (memLine.find("VmRSS:") == 0) {
                    std::istringstream memStream(memLine);
                    std::string label;
                    long memKb;
                    memStream >> label >> memKb;
                    // currently it would show in KB's , i'll convert it into MB , change if you want in kB
                    p.memory = memKb / 1024.0; // MB
                    break;
                  }
                }
            }
            result.push_back(p);
        }
    }
    closedir(dir);
    return result;
}
#include "../include/parser.hpp"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <limits.h> 


std::vector<ProcessInfo> parse_proc() {
    std::vector<ProcessInfo> result;
    DIR* dir = opendir("/proc");
    if (!dir) return result;

    
    double uptime = 0.0;
    { 
        std::ifstream temp_file("/proc/uptime");
        if( temp_file.is_open() ) temp_file >> uptime;
    }
    auto  hertz = sysconf(_SC_CLK_TCK);
    

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
            

            std::string comm,dummy;
            char state;
            unsigned long user_time, sys_time,start_time;
            iss.clear();
            iss.seekg(0);
            iss >> pid >> comm >> state;


            for(int i=0; i<10; i++) iss >> dummy; 
            iss >> user_time >> sys_time; 

            for(int i=0; i<4; i++) iss >> dummy; 
            iss >> start_time;
            
            if (!comm.empty() && comm.front() == '(' && comm.back() == ')') {
                comm = comm.substr(1, comm.size() - 2);
            }
            p.name = comm;
            // Israr - Get the executable path
            std::string exePath = "/proc/" + std::to_string(pid) + "/exe";
            char buf[PATH_MAX];
            ssize_t len = readlink(exePath.c_str(), buf, sizeof(buf) - 1);
            if (len != -1) {
                 buf[len] = '\0';
             p.path = std::string(buf);
            } else {
                p.path = "[unknown]";
            }
             // Israr - Calculated time and cpu usage along with memory
            auto total_time = user_time + sys_time;
            p.time = total_time / static_cast<double>(hertz);
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
                
                    p.memory = memKb / 1024.0; 
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
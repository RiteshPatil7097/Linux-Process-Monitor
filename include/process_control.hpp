#ifndef PROCESS_CONTROL_HPP
#define PROCESS_CONTROL_HPP

enum class ProcessAction {
    KILL,
    TERMINATE,
    SUSPEND,
    RESUME
};

bool control_process(int pid, ProcessAction action);

#endif 

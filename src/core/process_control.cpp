#include "process_control.hpp"
#include <signal.h>
#include <unistd.h>

bool control_process(int pid, ProcessAction action) {
    int sig = 0;
    switch (action) {
        case ProcessAction::KILL: sig = SIGKILL; break;
        case ProcessAction::TERMINATE: sig = SIGTERM; break;
        case ProcessAction::SUSPEND: sig = SIGSTOP; break;
        case ProcessAction::RESUME: sig = SIGCONT; break;
    }
    return kill(pid, sig) == 0;
}

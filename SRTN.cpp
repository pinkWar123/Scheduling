#include "SRTN.h"

SRTN::SRTN() {}

SRTN::SRTN(Data &d) : Scheduling(d.getProcess()) {}

void SRTN::Run()
{
    int time = 0;
    vector<Process> tempProcesses = process;
    while (true)
    {
    }
}
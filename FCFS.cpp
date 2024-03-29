#include "FCFS.h"
#include <iostream>

FCFS::FCFS(Data &d) : Scheduling(d.getProcess()) {}

void FCFS::Run()
{
    int time = 0;
    vector<Process> tempProcesses = process;
    while (true)
    {
        TakeProcessWithCurrentTime(tempProcesses, time);

        if (!TempQueue.empty())
        {
            for (int i = TempQueue.size() - 1; i >= 0; i--)
            {
                cpuQueue.push_back(TempQueue[i]);
            }
            TempQueue.clear();
        }

        int CurrentID = -1;
        if (!cpuQueue.empty())
        {
            UpdateWaitingTime();
            Process &temp = cpuQueue.front();
            --temp.CPUBurstTime[0];
            CPUScheduling.push_back(temp.ID);
            CurrentID = temp.ID;
            if (temp.CPUBurstTime[0] <= 0)
            {
                temp.CPUBurstTime.erase(temp.CPUBurstTime.begin());
                if (!temp.ResourceBurstTime.empty())
                {
                    ioQueue.push_back(temp);
                }
                cpuQueue.erase(cpuQueue.begin());
            }
        }
        else
            CPUScheduling.push_back(-1);

        bool flag = UpdateIOQueue(CurrentID, time);
        if (tempProcesses.empty() && ioQueue.empty() && cpuQueue.empty() && TempQueue.empty())
            break;
        if (flag)
            ++time;
    }
}
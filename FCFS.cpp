#include "FCFS.h"
#include <iostream>

FCFS::FCFS(Data &d) : Scheduling(d.getProcess()) {}

void FCFS::Run()
{
    int time = 0;
    vector<Process> tempProcesses = process;
    while (true)
    {
        // std::cout << process.size() << ' ' << ioQueue.size() << ' ' << cpuQueue.size() << endl;
        for (int i = 0; i < tempProcesses.size(); i++)
        {
            if (tempProcesses[i].ArrivalTime == time)
            {
                cpuQueue.push_back(tempProcesses[i]);
                tempProcesses.erase(tempProcesses.begin() + i);
                --i;
            }
        }
        int CurrentID = -1;
        if (!cpuQueue.empty())
        {
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

        if (!ioQueue.empty())
        {
            Process &temp = ioQueue.front();
            if (CurrentID == temp.ID)
            {
                ResourceScheduling.push_back(-1);
                time++;
                continue;
            }
            temp.ResourceBurstTime[0]--;
            ResourceScheduling.push_back(temp.ID);

            if (temp.ResourceBurstTime[0] <= 0)
            {
                temp.ResourceBurstTime.erase(temp.ResourceBurstTime.begin());
                if (!temp.CPUBurstTime.empty())
                {
                    cpuQueue.push_back(temp);
                }
                ioQueue.erase(ioQueue.begin());
            }
        }
        else
            ResourceScheduling.push_back(-1);
        if (tempProcesses.empty() && ioQueue.empty() && cpuQueue.empty())
            break;
        ++time;
    }
}
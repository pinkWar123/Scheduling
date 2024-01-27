#include "FCFS.h"
#include <iostream>
FCFS::FCFS(Data &d) : Scheduling(d.getProcess()) {}

void FCFS::Run()
{
    int time = 0;
    while (true)
    {
        if (process.empty() && ioQueue.empty() && cpuQueue.empty())
            break;
        for (int i = 0; i < process.size(); i++)
        {
            if (process[i].ArrivalTime == time)
            {
                cpuQueue.push(process[i]);
                process.erase(process.begin() + i);
                --i;
            }
        }
        if (!cpuQueue.empty())
        {
            Process &temp = cpuQueue.front();
            temp.CPUBurstTime[0]--;

            if (temp.CPUBurstTime[0] <= 0)
            {
                temp.CPUBurstTime.erase(temp.CPUBurstTime.begin());
                if (!temp.ResourceBurstTime.empty())
                {
                    ioQueue.push(temp);
                }
                cpuQueue.pop();
            }
            if (!cpuQueue.empty())
                CPUScheduling.push_back(cpuQueue.front().ID);
            else
                CPUScheduling.push_back(-1);
        }
        else
            CPUScheduling.push_back(-1);

        if (!ioQueue.empty())
        {
            Process &temp = ioQueue.front();
            temp.ResourceBurstTime[0]--;
            if (temp.ResourceBurstTime[0] <= 0)
            {
                temp.ResourceBurstTime.erase(temp.ResourceBurstTime.begin());
                if (!temp.CPUBurstTime.empty())
                {
                    cpuQueue.push(temp);
                }
                ioQueue.pop();
            }
            if (!ioQueue.empty())
                ResourceScheduling.push_back(ioQueue.front().ID);
            else
                ResourceScheduling.push_back(-1);
        }
        else
            ResourceScheduling.push_back(-1);

        ++time;
    }
}
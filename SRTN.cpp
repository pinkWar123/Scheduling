#include "SRTN.h"

SRTN::SRTN() {}

SRTN::SRTN(Data &d) : Scheduling(d.getProcess()) {}

void SRTN::Run()
{
    int time = 0;
    vector<Process> tempProcesses = process;
    while (true)
    {
        // UpdateCPUQueue(tempProcesses, time);
        for (int i = 0; i < tempProcesses.size(); i++)
        {
            if (tempProcesses[i].ArrivalTime == time)
            {
                cpuQueue.push_back(tempProcesses[i]);
                // ReadyQueue.push_back(tempProcesses[i]);
                tempProcesses.erase(tempProcesses.begin() + i);
                --i;
            }
        }
        int CurrentID = -1;

        if (!cpuQueue.empty())
        {
            int index = 0;
            for (int i = 1; i < cpuQueue.size(); i++)
            {
                if (cpuQueue[i].CPUBurstTime[0] <= cpuQueue[index].CPUBurstTime[0])
                    index = i;
            }
            if (index != 0)
            {
                cpuQueue.insert(cpuQueue.begin(), cpuQueue[index]);
                cpuQueue.erase(cpuQueue.begin() + index + 1);
            }
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

        // bool flag = UpdateIOQueue(CurrentID, time);
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
                    Process p = temp;
                    // ReadyQueue.push_back(p);
                    cpuQueue.push_back(p);
                }
                ioQueue.erase(ioQueue.begin());
            }
        }
        else
            ResourceScheduling.push_back(-1);
        if (hasAllProcessesCompleted(tempProcesses))
            break;
        ++time;
    }
}
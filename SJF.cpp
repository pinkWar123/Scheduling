#include "SJF.h"

SJF::SJF(Data &d) : Scheduling(d.getProcess()) {}

void SJF::InsertProcessIntoQueue(Process &other)
{
    if (cpuQueue.empty())
    {
        cpuQueue.push_back(other);
        return;
    }

    auto it = cpuQueue.begin();
    while (it != cpuQueue.end() && other.CPUBurstTime[0] > it->CPUBurstTime[0])
    {
        ++it;
    }

    cpuQueue.insert(it, other);
}
void SJF::Run()
{
    int currentTime = 0;
    vector<Process> tempProcesses = process;
    vector<Process> ReadyQueue;
    while (true)
    {
        for (int i = 0; i < tempProcesses.size();)
        {
            if (tempProcesses[i].ArrivalTime == currentTime)
            {
                InsertProcessIntoQueue(tempProcesses[i]);
                tempProcesses.erase(tempProcesses.begin() + i);
            }
            else
                ++i;
        }

        if (!ReadyQueue.empty())
        {
            SortReadyQueue();
            for (int i = 0; i < ReadyQueue.size(); i++)
            {
                InsertProcessIntoQueue(ReadyQueue[i]);
            }
            ReadyQueue.clear();
        }

        int CurrentID = -1;
        if (!cpuQueue.empty())
        {
            UpdateWaitingTime();
            Process &temp = cpuQueue.front();
            CurrentID = temp.ID;
            --temp.CPUBurstTime[0];
            CPUScheduling.push_back(temp.ID);
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
                currentTime++;
                continue;
            }
            --temp.ResourceBurstTime[0];
            ResourceScheduling.push_back(temp.ID);
            if (temp.ResourceBurstTime[0] <= 0)
            {
                temp.ResourceBurstTime.erase(temp.ResourceBurstTime.begin());
                if (!temp.CPUBurstTime.empty())
                {
                    Process p = temp;
                    ReadyQueue.push_back(p);
                }
                ioQueue.erase(ioQueue.begin());
            }
        }
        else
            ResourceScheduling.push_back(-1);

        if (hasAllProcessesCompleted(tempProcesses) && ReadyQueue.empty())
            break;
        currentTime++;
    }
}

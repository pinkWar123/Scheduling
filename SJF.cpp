#include "SJF.h"

SJF::SJF(Data &d) : Scheduling(d.getProcess()) {}

void SJF::InsertProcessIntoQueue(Process &other)
{
    if (cpuQueue.empty())
    {
        cpuQueue.push_back(other);
        return;
    }
    bool flag = true;
    for (int i = 0; i < cpuQueue.size() - 1; i++)
    {
        if (other.CPUBurstTime[0] >= cpuQueue[i].CPUBurstTime[0] && other.CPUBurstTime[0] <= cpuQueue[i + 1].CPUBurstTime[0])
        {
            flag = false;
            cpuQueue.insert(cpuQueue.begin() + i + 1, other);
            break;
        }
    }
    if (flag)
        cpuQueue.push_back(other);
}

void SJF::Run()
{
    int currentTime = 0;
    vector<Process> tempProcesses = process;
    while (true)
    {
        // Chèn các tiến trình mới đến vào hàng đợi CPU
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

        int CurrentID = -1;
        if (!cpuQueue.empty())
        {
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
                    InsertProcessIntoQueue(temp);
                }
                ioQueue.erase(ioQueue.begin());
            }
        }
        else
            ResourceScheduling.push_back(-1);

        if (tempProcesses.empty() && cpuQueue.empty() && ioQueue.empty())
            break;
        currentTime++;
    }
}

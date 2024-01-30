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
    it++;
    while (it != cpuQueue.end() && other.CPUBurstTime[0] >= it->CPUBurstTime[0])
    {
        ++it;
    }

    cpuQueue.insert(it, other);
}
void SJF::Run()
{
    int currentTime = 0;
    vector<Process> tempProcesses = process;
    while (true)
    {
        TakeProcessWithCurrentTime(tempProcesses, currentTime);

        if (!TempQueue.empty())
        {
            for (int i = TempQueue.size() - 1; i >= 0; i--)
            {
                InsertProcessIntoQueue(TempQueue[i]);
            }
            TempQueue.clear();
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

        bool flag = UpdateIOQueue(CurrentID, currentTime);

        if (hasAllProcessesCompleted(tempProcesses) && TempQueue.empty())
            break;
            
        if(flag)
            currentTime++;
    }
}

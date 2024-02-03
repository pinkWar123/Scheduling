#include "SRTN.h"

SRTN::SRTN() {}

SRTN::SRTN(Data &d) : Scheduling(d.getProcess()) {}
void SRTN::InsertProcessIntoQueue(Process &other)
{
    if (cpuQueue.empty())
    {
        cpuQueue.push_back(other);
        return;
    }

    auto it = cpuQueue.begin();
    while (it != cpuQueue.end() && other.CPUBurstTime[0] >= it->CPUBurstTime[0])
    {
        ++it;
    }

    cpuQueue.insert(it, other);
}
void SRTN::Run()
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
                InsertProcessIntoQueue(TempQueue[i]);
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
        if (hasAllProcessesCompleted(tempProcesses) && TempQueue.empty())
            break;
        if(flag)
            ++time;
    }
}
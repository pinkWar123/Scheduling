#include "RoundRobin.h"

void RoundRobin::Run()
{
    int currentTime = 0;
    int count = 0;
    bool allProcessesCompleted = false;
    bool AddIntoQueue = false;
    while (true)
    {
        // Arrival time check and process queueing
        for (int i = 0; i < process.size();)
        {
            if (process[i].ArrivalTime == currentTime)
            {
                cpuQueue.push(process[i]);
                process.erase(process.begin() + i);
                if (process.empty())
                    allProcessesCompleted = true;
            }
            else
                ++i;
        }
        if (AddIntoQueue)
        {
            AddIntoQueue = false;
            cpuQueue.push(cpuQueue.front());
            cpuQueue.pop();
        }
        int CurrentID = -1;
        if (!cpuQueue.empty())
        {
            Process &temp = cpuQueue.front();
            CurrentID = temp.ID;
            ++count;
            --temp.CPUBurstTime[0];

            if (temp.CPUBurstTime[0] <= 0)
            {
                temp.CPUBurstTime.erase(temp.CPUBurstTime.begin());
                if (!temp.ResourceBurstTime.empty())
                    ioQueue.push(temp);
                cpuQueue.pop();
                count = 0;
            }
            else if (count == time_quantum)
            {
                AddIntoQueue = true;
                count = 0;
            }
            CPUScheduling.push_back(temp.ID);
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
            if (temp.ResourceBurstTime[0] <= 0)
            {
                temp.ResourceBurstTime.erase(temp.ResourceBurstTime.begin());
                if (!temp.CPUBurstTime.empty())
                    cpuQueue.push(temp);

                ioQueue.pop();
            }
            ResourceScheduling.push_back(temp.ID);
        }
        else
            ResourceScheduling.push_back(-1);

        if (allProcessesCompleted && cpuQueue.empty() && ioQueue.empty())
            break;

        currentTime++;
    }
}
#include "RoundRobin.h"

void RoundRobin::Run()
{
    int currentTime = 0;
    int count = 0;
    bool allProcessesCompleted = false;

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

        // CPU Queue handling
        if (!cpuQueue.empty())
        {
            Process &temp = cpuQueue.front();

            if (temp.CPUBurstTime[0] <= 0)
            {
                temp.CPUBurstTime.erase(temp.CPUBurstTime.begin());

                if (!temp.ResourceBurstTime.empty())
                    ioQueue.push(temp);

                cpuQueue.pop(); 
                count = 0;
            }
            else
            {
                --temp.CPUBurstTime[0];
                ++count;
                if (count == time_quantum)
                {
                    cpuQueue.pop(); 
                    cpuQueue.push(temp);
                    count = 0;
                }

                CPUScheduling.push_back(temp.ID);
            }
        }
        else
        {
            CPUScheduling.push_back(-1);
        }

        // I/O Queue handling
        if (!ioQueue.empty())
        {
            Process &temp = ioQueue.front();

            if (temp.ResourceBurstTime[0] <= 0)
            {
                temp.ResourceBurstTime.erase(temp.ResourceBurstTime.begin());

                if (!temp.CPUBurstTime.empty())
                    cpuQueue.push(temp);

                ioQueue.pop(); 
            }
            else
            {
                --temp.ResourceBurstTime[0];
                ResourceScheduling.push_back(temp.ID);
            }
        }
        else
        {
            ResourceScheduling.push_back(-1);
        }

        // Check if all processes are done
        if (allProcessesCompleted && cpuQueue.empty() && ioQueue.empty())
        {
            break;
        }

        ++currentTime;
    }
}

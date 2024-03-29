#include "RoundRobin.h"

void RoundRobin::Run()
{
    int currentTime = 0;
    int count = 0;
    bool AddIntoQueue = false;
    vector<Process> tempProcesses = process;
    while (true)
    {
        // Arrival time check and process queueing
        TakeProcessWithCurrentTime(tempProcesses, currentTime);
        if (!TempQueue.empty())
        {
            for (int i = TempQueue.size() -1 ; i >= 0; i--)
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
            CurrentID = temp.ID;
            ++count;
            --temp.CPUBurstTime[0];
            CPUScheduling.push_back(temp.ID);

            if (temp.CPUBurstTime[0] <= 0)
            {
                temp.CPUBurstTime.erase(temp.CPUBurstTime.begin());
                if (!temp.ResourceBurstTime.empty())
                    ioQueue.push_back(temp);
                cpuQueue.erase(cpuQueue.begin());
                count = 0;
            }
            else if (count == time_quantum)
            {
                Process p = temp;
                TempQueue.push_back(p);
                cpuQueue.erase(cpuQueue.begin());
                count = 0;
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
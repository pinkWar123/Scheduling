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
            for (int i = 0; i < cpuQueue.size(); i++)
            {
                if (cpuQueue[i].CPUBurstTime[0] <= cpuQueue[index].CPUBurstTime[0])
                    index = i;
            }
            vector<int> minIndexes;
            for (int i = 0; i < cpuQueue.size(); i++)
            {
                if (cpuQueue[i].CPUBurstTime[0] == cpuQueue[index].CPUBurstTime[0])
                    minIndexes.push_back(i);
            }
            int minIndex = 0;
            vector<int> hasAlreadyUsedCpuIndexes;
            vector<int> hasNotAlreadyUsedCpuIndexes;
            for (int i = 0; i < minIndexes.size(); i++)
            {
                int index = minIndexes[i];
                bool flag = true;
                for (int j = 0; j < CPUScheduling.size(); j++)
                {
                    if (CPUScheduling[j] == cpuQueue[index].ID)
                    {
                        hasAlreadyUsedCpuIndexes.push_back(index);
                        flag = false;
                        break;
                    }
                }
                if (flag)
                    hasNotAlreadyUsedCpuIndexes.push_back(index);
            }
            cout << hasNotAlreadyUsedCpuIndexes.size() << endl;
            if (!hasNotAlreadyUsedCpuIndexes.empty())
            {
                minIndex = hasNotAlreadyUsedCpuIndexes.front();
            }
            else
            {
                vector<int> history;
                for (int i = 0; i < hasAlreadyUsedCpuIndexes.size(); i++)
                {
                    for (int j = CPUScheduling.size() - 1; j >= 0; j--)
                    {
                        if (CPUScheduling[j] == cpuQueue[hasAlreadyUsedCpuIndexes[i]].ID)
                        {
                            history.push_back(j);
                            break;
                        }
                    }
                }
                for (int i = 0; i < history.size(); i++)
                {
                    if (history[i] < history[minIndex])
                        minIndex = i;
                }
                minIndex = hasAlreadyUsedCpuIndexes[minIndex];
            }

            if (minIndex != 0)
            {
                cpuQueue.insert(cpuQueue.begin(), cpuQueue[minIndex]);
                cpuQueue.erase(cpuQueue.begin() + minIndex + 1);
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
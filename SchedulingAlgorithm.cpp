#include "SchedulingAlgorithm.h"

Scheduling::Scheduling() {}
Scheduling::Scheduling(vector<Process> p)
{
    this->process = p;
}
void Scheduling::CalculateTurnAroundTime()
{
    for (int i = 0; i < process.size(); i++)
    {
        int timeCompleted1 = 0;
        int timeCompleted2 = 0;
        for (int j = 0; j < CPUScheduling.size(); j++)
        {
            if (CPUScheduling[j] == process[i].ID)
                timeCompleted1 = j;
        }
        for (int j = 0; j < ResourceScheduling.size(); j++)
        {
            if (ResourceScheduling[j] == process[i].ID)
                timeCompleted2 = j;
        }

        int total = 0;
        for (int j = process[i].ArrivalTime; j < CPUScheduling.size(); j++)
            if (CPUScheduling[j] != process[i].ID)
                ++total;
        process[i].turnArroundTime = max(timeCompleted1, timeCompleted2) - process[i].ArrivalTime + 1;
        // process[i].WaitTime = total;
    }
}

void Scheduling::UpdateWaitingTime()
{
    for (int i = 1; i < cpuQueue.size(); i++)
    {
        int id = cpuQueue[i].ID;
        process[id - 1].WaitTime++;
    }
}

bool Scheduling::hasAllProcessesCompleted(vector<Process> &p)
{
    return p.empty() && cpuQueue.empty() && ioQueue.empty();
}

void Scheduling::takeProcesswithCurrenttime(vector<Process> &tempProcesses, int time)
{
    for (int i = 0; i < tempProcesses.size(); i++)
    {
        if (tempProcesses[i].ArrivalTime == time)
        {
            ProcesswaitedintoCPUQueue.push_back(tempProcesses[i]);
            tempProcesses.erase(tempProcesses.begin() + i);
            --i;
        }
    }
}
// void Scheduling::SortReadyQueue()
// {
//     for (int i = 0; i < ReadyQueue.size(); i++)
//     {
//         for (int j = i + 1; j < ReadyQueue.size(); j++)
//         {
//             if (ReadyQueue[i].ArrivalTime < ReadyQueue[j].ArrivalTime)
//             {
//                 swap(ReadyQueue[i], ReadyQueue[j]);
//             }
//         }
//     }
// }
bool Scheduling::UpdateIOQueue(int CurrentID, int &time)
{
    if (!ioQueue.empty())
    {
        Process &temp = ioQueue.front();
        if (CurrentID == temp.ID)
        {
            ResourceScheduling.push_back(-1);
            time++;
            return false;
        }
        temp.ResourceBurstTime[0]--;
        ResourceScheduling.push_back(temp.ID);

        if (temp.ResourceBurstTime[0] <= 0)
        {
            temp.ResourceBurstTime.erase(temp.ResourceBurstTime.begin());
            if (!temp.CPUBurstTime.empty())
            {
                Process p = temp;
                ProcesswaitedintoCPUQueue.push_back(p);
            }
            ioQueue.erase(ioQueue.begin());
        }
    }
    else
        ResourceScheduling.push_back(-1);
    return true;
}

void Scheduling::WriteIntoFile(const char *filename)
{
    CalculateTurnAroundTime();
    ofstream os(filename);
    for (int i = 0; i < CPUScheduling.size(); i++)
    {
        if (CPUScheduling[i] == -1)
            os << "_";
        else
            os << CPUScheduling[i];

        os << " ";
    }
    os << endl;
    for (int i = 0; i < ResourceScheduling.size(); i++)
    {
        if (ResourceScheduling[i] == -1)
            os << "_";
        else
            os << ResourceScheduling[i];

        os << " ";
    }
    os << endl;
    for (int i = 0; i < process.size(); i++)
    {
        os << process[i].turnArroundTime << " ";
    }
    os << endl;
    for (int i = 0; i < process.size(); i++)
    {
        os << process[i].WaitTime << " ";
    }
    os.close();
}
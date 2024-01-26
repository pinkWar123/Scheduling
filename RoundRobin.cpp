#include "RoundRobin.h"

void RoundRobin::Run()
{
    int currentTime = 0;
    int count = 0;
    bool allIsDone = false;
    while(true)
    {
        for(int i = 0; i < process.size(); i++)
        {
            if(process[i].ArrivalTime == currentTime)
            {
                cpuQueue.push(process[i]);
                process.erase(process.begin() + i--);
                if(process.size() == 0)
                    allIsDone = true;
            }
        }

        if(!cpuQueue.empty())
        {
            Process temp = cpuQueue.front();
            --temp.CPUBurstTime[0];
            if(temp.CPUBurstTime[0] == 0)
            {
                temp.CPUBurstTime.erase(temp.CPUBurstTime.begin());
                if(!temp.ResourceBurstTime.empty())
                    ioQueue.push(temp);
                cpuQueue.pop();
            }
            else{
                CPUsheduling.push_back(temp.ID);
            }
        }
    }
}
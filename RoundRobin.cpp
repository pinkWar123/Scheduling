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
                count = 0;
            }
            else{
                ++count;
                if(count == time_quantum)
                {
                    cpuQueue.pop();
                    cpuQueue.push(temp);
                    count = 0;
                }
                CPUsheduling.push_back(temp.ID);
            }
        }
        else
            CPUsheduling.push_back(-1);

            
        if(!ioQueue.empty())
        {
            Process temp = ioQueue.front();
            --temp.ResourceBurstTime[0];
            if(temp.ResourceBurstTime[0] == 0)
            {
                temp.ResourceBurstTime.erase(temp.ResourceBurstTime.begin());
                if(!temp.CPUBurstTime.empty())
                    cpuQueue.push(temp);
                ioQueue.pop();
            }
            else
            {
                Resourcesheduling.push_back(temp.ID);
            }
        }
        else if(ioQueue.empty())
        {
            Resourcesheduling.push_back(-1);
        }

        if(allIsDone && cpuQueue.empty() && ioQueue.empty())
        {
            break;
        }
        currentTime++;
    }
}
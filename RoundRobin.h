#include "ShedulingAlgorithm.h"

class RoundRobin : Sheduling
{
private:
    int time_quantum;

public:
    RoundRobin(Data d) : Sheduling(d.getProcess())
    {
        time_quantum = d.getTime_quantum();
    }
    void Run() override;
};
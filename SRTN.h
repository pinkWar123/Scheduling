#pragma once
#include "SchedulingAlgorithm.h"
#include <algorithm>
class SRTN : public Scheduling
{
public:
    SRTN();
    SRTN(Data &d);
    void Run() override;
    void InsertProcessIntoQueue(Process &other);
};

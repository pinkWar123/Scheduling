#include "SchedulingAlgorithm.h"

class SRTN : public Scheduling
{
public:
    SRTN();
    SRTN(Data &d);
    void Run() override;
};

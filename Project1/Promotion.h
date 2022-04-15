#pragma once
#include "Event.h"
class Promotion :
    public Event

{
    int id;
public:
    Promotion(Time eventTime, int id);
    void Execute();

};


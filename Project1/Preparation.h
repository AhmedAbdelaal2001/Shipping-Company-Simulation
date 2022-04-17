#pragma once
#include "Event.h"

class Perparation :
    public Event
{
private:
    char type;
    int distance;
    int cost;
    Time loadTime;

public:
    Perparation(Time eventTime, Company* pCompany, int id, char type, int distance, int cost, Time loadTime);

    bool Execute();
};


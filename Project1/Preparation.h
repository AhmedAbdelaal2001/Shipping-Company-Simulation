#pragma once
#include "Event.h"
#include "Company.h"

class Perparation :
    public Event
{
private:
    char type;
    int distance;
    int cost;
    int loadTime;

public:
    Perparation(Time eventTime, Company* pCompany, int id, char type, int distance, int cost, int loadTime);

    bool Exectue();
};


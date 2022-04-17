#pragma once
#include "Event.h"


class Promotion :
    public Event

{
    int extraCost;

public:
    
    Promotion(Time eventTime, Company* pCompany, int id, int extraCost = 0);
    
    bool Execute();


};


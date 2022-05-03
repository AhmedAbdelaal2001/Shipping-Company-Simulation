#pragma once
#include "Event.h"


class Promotion :
    public Event

{
    int extraCost;

public:
    
    Promotion(Company* pCompany);
    
    bool Execute() override;       // promotes normal cargo to VIP by dequeueing from the waiting normal and enqueueing in the VIPwaiting

    void load(ifstream& inputFile) override;  // loads data from file


};


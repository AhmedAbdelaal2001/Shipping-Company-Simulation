#pragma once
#include "Event.h"


class Promotion :
    public Event

{
    int extraCost;

public:
    
    Promotion(Company* pCompany);
    
    bool Execute() override;

    void load(ifstream& inputFile) override;


};


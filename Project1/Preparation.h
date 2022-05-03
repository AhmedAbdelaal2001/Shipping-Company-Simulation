#pragma once
#include "Event.h"

class Preparation :
    public Event
{
private:
    char cargoType;
    int distance;
    int cost;
    int loadTime;

public:
    Preparation(Company* pCompany);

    bool Execute() override;      // prepares the cargo and enqueues it in the appropriate waiting list
    void load(ifstream& inputFile) override;   // loads the data from file
};


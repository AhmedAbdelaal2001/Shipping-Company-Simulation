#pragma once
#include "Event.h"

class Perparation :
    public Event
{
private:
    char cargoType;
    int distance;
    int cost;
    Time loadTime;

public:
    Perparation(Company* pCompany);

    bool Execute() override;
    void load(ifstream& inputFile) override;
};


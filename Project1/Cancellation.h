#pragma once
#include "Event.h"


class Cancellation :
    public Event
{

public:

    Cancellation(Company* pCompany);

    bool Execute() override; // to execute

    void load(ifstream& inputFile) override; // to load data
};


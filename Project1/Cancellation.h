#pragma once
#include "Event.h"


class Cancellation :
    public Event
{

public:

    Cancellation(Company* pCompany);

    bool Execute() override;

    void load(ifstream& inputFile) override;
};


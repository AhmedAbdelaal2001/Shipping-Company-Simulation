#pragma once
#include "Event.h"
class Cancellation :
    public Event
{
    int id;

public:

    Cancellation(Time eventTime, Company* pCompany, int id);

    bool Execute();
};


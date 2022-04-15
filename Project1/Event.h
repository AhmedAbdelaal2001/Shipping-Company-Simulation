#pragma once
#include "Time.h"
#include "Cargo.h"

class Event
{
private:
	Time eventTime;

public:
	Event(Time eventTime);

	virtual void Execute() = 0;
};


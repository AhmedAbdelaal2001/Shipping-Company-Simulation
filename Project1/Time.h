#pragma once
#include<iostream>
using namespace std;
class Time
{

private:
	
	int days;
	int hours;

public:
	
	Time(int hour = 0, int day = 0);
	Time(const Time& time);

	int getHours() const;
	void setHours(int hour);

	int getDays() const;
	void setDays(int day);

	void operator ++();
	Time operator +(Time time);
	Time operator -(Time time);
	bool operator >=(Time time);
	void printTime();

};




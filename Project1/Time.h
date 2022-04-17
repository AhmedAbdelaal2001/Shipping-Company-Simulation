#pragma once
#include<iostream>
using namespace std;
class Time
{

private:
	
	int days;
	int hours;

public:
	
	Time(int days = 0, int hours = 0);
	Time(const Time& time);

	int getHours() const;
	void setHours(int hour);

	int getDays() const;
	void setDays(int day);

	void printTime();
	
	void operator ++();
	Time operator +(Time time);
	Time operator -(Time time);
	bool operator >=(Time time);
	Time operator /(int count);

	friend ostream& operator << (ostream& out, const Time time);

};




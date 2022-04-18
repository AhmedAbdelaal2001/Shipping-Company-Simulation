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
	
	Time& operator ++();
	Time operator +(Time time);
	Time operator -(Time time);
	bool operator >=(Time time);
	Time operator /(int count);
	bool operator ==(const Time& time);
	int operator % (int divisor);

	friend ostream& operator << (ostream& out, const Time time);

};




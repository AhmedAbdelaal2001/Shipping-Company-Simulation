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
	
	Time& operator ++();				// for incrementing timesteps
	Time operator +(Time time);			// to add 2 times
	Time operator -(Time time);			// to subtract 2 times
	bool operator >=(Time time);		// to compare if time1 is greater than or equal time2
	Time operator /(int count);			// to divide 2 times
	bool operator ==(const Time& time);	// returns true if times are equal
		

	friend ostream& operator << (ostream& out, const Time time);

};




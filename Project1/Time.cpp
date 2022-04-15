#include "Time.h"

Time::Time(int hour, int day) {
	
	setHours(hour);
	setDays(day);

}

Time::Time(const Time& time)
{
	setDays(time.getDays());
	setHours(time.getHours());
}

int Time::getHours() const {
	return hours;
}

void Time::setHours(int hour) {
	this->hours = hour;
}

int Time::getDays() const {
	return days;
}

void Time::setDays(int day) {
	this->days = day;
}
void Time::printTime()
{
	cout << days << ":" << hours << endl;
}
void Time:: operator ++() {
	if (hours + 1 == 24) {
		days++;
		hours = 0;
	}
	else
		hours++;
}
Time Time::operator +(Time time) {
	int currHours = hours;
	int addedHours = time.getHours();
	int newHours = currHours + addedHours;
	int newDays = days + time.getDays();

	if (newHours >= 24) {
		newHours -= 24;
		newDays++;
	}
	Time result(newDays, newHours);
	return result;

}
Time Time::operator -(Time time) {
	int currHours = hours;
	int subtractedHours = time.getHours();
	int newHours = currHours - subtractedHours;
	int newDays = days - time.getDays();

	if (newHours < 0) {
		newHours += 24;
		newDays--;
	}

	Time result(newDays, newHours);
	return result;

}
bool Time::operator >=(Time time) {

	if (days > time.getDays())
		return true;
	else if (days == time.getDays())
		return hours > time.getHours();
	
	return false;
}

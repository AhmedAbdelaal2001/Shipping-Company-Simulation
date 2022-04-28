#include "Time.h"

Time::Time(int days, int hours) {
	
	setHours(hours);
	setDays(days);

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
	
	days += hour / 24;
	hours = hour % 24;
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
Time& Time::operator++() {
	if (hours + 1 == 24) {
		days++;
		hours = 0;
	}
	else
		hours++;

	return *this;
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

Time Time::operator /(int count) {
	int totalHours = days * 24 + hours;

	int result = totalHours / count;

	Time division(0, result);
	
	
	return division;
}

bool Time::operator ==(const Time& time) {
	return hours == time.getHours() && days == time.getDays();
}

ostream& operator << (ostream& out, const Time time) {
	out << time.days << ":" << time.hours << "	";
	return out;
}

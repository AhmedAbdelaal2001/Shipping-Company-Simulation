#include "CrossLinkedList.h"
#include "PriorityQueue.h"
#include "Time.h"
#include "Queue.h"

ostream& operator << (ostream& out, Node<int*> node) {
	out << *node.getItem();

	return out;
}

void TimeTest() {
	int day1, hour1, day2, hour2;
	cin >> day1 >> hour1 >> day2 >> hour2;
	Time time1(day1, hour1), time2(day2, hour2);
	Time sum;
	sum = time1 + time2;
	sum.printTime();

	Time difference;
	difference = time1 - time2;
	difference.printTime();

}

//This main function is for testing the custom crosslinked list (using a HashMap). Run the program and follow the prompts.
int main() {

	QueueTest();
	return 0;
}
#include "ArrayList.h"

int main() {
	
	int choice = 0;
	int inputNum1 = 0;
	int inputNum2 = 0;
	bool check = true;
	char decision;


	cout << "Creating List: " << endl;
	ArrayList<int> list(3);
	cout << "List Created!" << endl;
	
	while (check) {
		
		cout << "**********************************************************************************" << endl;
		cout << "1. Insert at the end:" << endl;
		cout << "2. Delete From the end:" << endl;
		cout << "3. Swap 2 elements: " << endl;
		cout << "4. Print the List: " << endl;
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Input the number you wish to insert: ";
			cin >> inputNum1;
			list.insertEnd(inputNum1);
			cout << "Element Inserted." << endl;
			break;

		case 2:
			cout << "Deleting the last element: " << endl;
			check = list.deleteEnd();

			if (check)
				cout << "Last element deleted." << endl;
			else
				cout << "List already empty." << endl;
			
			break;

		case 3:
			cout << "Enter the index of the first number: ";
			cin >> inputNum1;
			cout << "Enter the index of the second number: ";
			cin >> inputNum2;
			check = list.swap(inputNum1, inputNum2);

			if (check)
				cout << "Items swapped" << endl;
			else
				cout << "Items could not be swapped" << endl;

			break;

		case 4:
			cout << "Printing the list: " << endl;
			list.PrintList();
			cout << "List Printed." << endl;
			break;
		}

		cout << "Do you wish to continue? (y/n)";
		cin >> decision;
		if (decision == 'y')
			check = true;
		else
			check = false;
	}

	return 0;
}
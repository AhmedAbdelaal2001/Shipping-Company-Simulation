#include "CrossLinkedList.h"

ostream& operator << (ostream& out, Node<int> node) {
	out << *(node.getItemPtr());

	return out;
}

//This main function is for testing the Priority Queue. Run the program and follow the prompts.
int main() {

	CrossLinkedListTest();

	return 0;
}
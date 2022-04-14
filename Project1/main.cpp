#include "CrossLinkedList.h"

ostream& operator << (ostream& out, Node<int> node) {
	out << *(node.getItemPtr());

	return out;
}

//This main function is for testing the custom crosslinked list (using a HashMap). Run the program and follow the prompts.
int main() {

	CrossLinkedListTest();

	return 0;
}
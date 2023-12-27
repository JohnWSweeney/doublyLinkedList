#include "doublyLinkedList.h"

int main()
{
	printf("Doubly Linked List v0.0.0\n\n");
	int result;
	struct node* list = NULL;

	/// test code here: ////////////////////////////////////////
	result = addBack(&list, 987);
	result = addBack(&list, 123);
	result = addBack(&list, 321);
	printf("result: %d\n", result);
	print(list);
	////////////////////////////////////////////////////////////
}
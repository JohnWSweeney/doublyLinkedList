#include "doublyLinkedList.h"

int main()
{
	printf("Doubly Linked List v0.0.9\n\n");
	int result;
	int nodeCount;
	int position;
	int data;
	struct dNode* list = NULL;
	struct dNode* ptr = NULL;

	for (int i = 0; i < 9; i++)
	{
		addBack(&list, pow(i, 5));
	}
	result = size(list, &nodeCount);
	if (result == 0)
	{
		printf("Node count: %d\n", nodeCount);
		print(list);
	}
	else
	{
		printf("List is empty.\n\n");
	}
	/// test code here: ////////////////////////////////////////
	position = 3;
	result = returnPosPtr(list, position, &ptr);
	////////////////////////////////////////////////////////////
	result = movePtrBack(&list, ptr);
	printf("Result: %d\n\n", result);
	////////////////////////////////////////////////////////////
	result = size(list, &nodeCount);
	if (result == 0)
	{
		printf("Node count: %d\n", nodeCount);
		print(list);
	}
	else
	{
		printf("List is empty.\n\n");
	}
}
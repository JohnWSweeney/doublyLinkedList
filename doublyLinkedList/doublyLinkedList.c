#include "doublyLinkedList.h"
// sweeney's hand-rolled doubly linked list.
//
// pos = "position".
// ptr = "pointer".
//
// error codes:
// 0	no error.
// 1	list is NULL.
// 2	ptr is NULL.
// 5	list has only one node.
// -1	pos/ptr not in list.
// -2	no action needed.

struct dNode* init(int data)
{
	struct dNode* newNode = malloc(sizeof(struct dNode));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

int addFront(struct dNode** list, int data)
{
	if (*list == NULL)
	{
		*list = init(data);
		return 0;
	}

	struct dNode* head = *list;
	struct dNode* newNode = malloc(sizeof(struct dNode));
	newNode->data = data;
	newNode->next = head;
	newNode->prev = NULL;
	head->prev = newNode;
	*list = newNode;
	return 0;
}

int addBack(struct dNode** list, int data)
{
	if (*list == NULL) // initialize empty list.
	{
		*list = init(data);
		return 0;
	}

	struct dNode* head = *list;
	do {
		struct dNode* curr = *list;
		if (curr->next == NULL)
		{
			struct dNode* newNode = malloc(sizeof(struct dNode));
			newNode->data = data;
			curr->next = newNode;
			newNode->prev = curr;
			newNode->next = NULL;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != NULL);
}

int deleteFront(struct dNode** list)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list;
	struct dNode* newHead = head->next;
	newHead->prev = NULL;
	free(head);
	*list = newHead;
	return 0;
}

int deleteBack(struct dNode* list)
{
	if (list == NULL) return 1; // list is empty.

	do {
		struct dNode* dummy = list->next;
		if (dummy->next == NULL)
		{
			free(dummy);
			list->next = NULL;
			return 0;
		}
		list = list->next;
	} while (list != NULL);
}

int clear(struct dNode** list)
{
	if (*list == NULL) return 1; // list is empty.

	do {
		struct dNode* dummy = *list;
		*list = dummy->next;
		free(dummy);
	} while (*list != NULL);
	return 0;
}

int isEmpty(struct dNode* list)
{
	if (list == NULL) return 1; // list is empty.
	else return 0;
}

int size(struct dNode* list, int* nodeCount)
{
	*nodeCount = 0;
	if (list == NULL) return 1; // list is empty.

	do {
		++*nodeCount;
		list = list->next;
	} while (list != NULL);
	return 0;
}

int print(struct dNode* list)
{
	if (list == NULL) return 1; // list is empty.

	printf("#\tdata:\tcurr:\t\t\tnext:\t\t\tprev:\n");
	int tempPos = 0;
	do {
		printf("%d\t%d\t%p\t%p\t%p\n", tempPos, list->data, list, list->next, list->prev);
		++tempPos;
		list = list->next;
	} while (list != NULL);
	printf("\n\n");
	return 0;
}
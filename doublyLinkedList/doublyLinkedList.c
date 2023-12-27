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

int addPos(struct dNode** list, int pos, int data)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list;
	struct dNode* before = NULL; // node before current node in list.
	struct dNode* curr = NULL; // current node.
	int tempPos = 0;
	do {
		curr = *list;
		if (tempPos == pos)
		{
			struct dNode* newNode = malloc(sizeof(struct dNode));
			newNode->data = data;
			before = curr->prev;
			if (before != NULL) // check if previous node is null.
			{
				before->next = newNode;
				
			}
			else // else, current node is head node.
			{
				head = newNode; // assign new head node.
			}
			newNode->prev = before;
			newNode->next = curr;
			curr->prev = newNode;
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != NULL);
	*list = head; // position not in list, reset list.
	return -1;
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

int deletePos(struct dNode** list, int pos)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list;
	struct dNode* before = NULL; // node before current node in list.
	struct dNode* curr = NULL; // current node.
	struct dNode* after = NULL; // node after current node in list.
	int tempPos = 0;
	do {
		curr = *list;
		if (tempPos == pos)
		{
			before = curr->prev;
			after = curr->next;
			if (before != NULL) // check if previous node is null.
			{
				before->next = after;
			}
			if (after != NULL) // check if next node is null.
			{
				after->prev = before;
			}
			if (curr == head) // reassign head node if pos == 0.
			{
				head = head->next;
			}
			free(curr);
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != NULL);
	*list = head; // position not in list, reset list.
	return -1;
}

int deletePtr(struct dNode** list, struct dNode* ptr)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list;
	struct dNode* before = NULL;
	struct dNode* curr = NULL;
	struct dNode* after = NULL;
	do {
		curr = *list;
		if (curr == ptr)
		{
			before = curr->prev;
			after = curr->next;
			if (before != NULL)
			{
				before->next = after;
			}
			if (after != NULL)
			{
				after->prev = before;
			}
			if (ptr == head)
			{
				head = head->next;
			}
			free(curr);
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != NULL);
	*list = head; // pointer not in list, reset list.
	return -1;
}

int returnPosPtr(struct dNode* list, int pos, struct dNode** ptr)
{
	if (list == NULL) return 1; // list is empty.

	struct dNode* head = list;
	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			*ptr = list;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != NULL);
	return -1;
}

int returnPtrPos(struct dNode* list, struct dNode* ptr, int* pos)
{
	if (list == NULL) return 1; // list is empty.

	struct dNode* head = list;
	*pos = 0;
	do {
		if (list == ptr)
		{
			return 0;
		}
		++*pos;
		list = list->next;
	} while (list != NULL);
}

int returnPosData(struct dNode* list, int pos, int* data)
{
	if (list == NULL) return 1; // list is empty.

	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			*data = list->data;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != NULL);
	return -1; // position not in list.
}

int returnPtrData(struct dNode* list, struct dNode* ptr, int* data)
{
	if (list == NULL) return 1; // list is empty.

	do {
		if (list == ptr)
		{
			*data = list->data;
			return 0;
		}
		list = list->next;
	} while (list != NULL);
	return -1; // pointer not in list.
}

int updatePosData(struct dNode* list, int pos, int data)
{
	if (list == NULL) return 1; // list is empty.

	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			list->data = data;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != NULL);
	return -1; // position not in list.
}

int updatePtrData(struct dNode* list, struct dNode* ptr, int data)
{
	if (list == NULL) return 1; // list is empty.

	do {
		if (list == ptr)
		{
			list->data = data;
			return 0;
		}
		list = list->next;
	} while (list != NULL);
	return -1; // pointer not in list.
}

int returnDataPos(struct dNode* list, int data, int* pos)
{
	if (list == NULL) return 1; // list is empty.

	*pos = 0;
	do {
		if (list->data == data)
		{
			return 0;
		}
		++*pos;
		list = list->next;
	} while (list != NULL);
	return -1; // data not in list.
}

int returnDataPtr(struct dNode* list, int data, struct dNode** ptr)
{
	if (list == NULL) return 1; // list is empty.

	do {
		if (list->data == data)
		{
			*ptr = list;
			return 0;
		}
		list = list->next;
	} while (list != NULL);
	return -1; // data not in list.
}

int returnMinPos(struct dNode* list, int* min, int* pos)
{
	if (list == NULL) return 1; // list is empty.

	// initialize result with first node.
	*min = list->data;
	*pos = 0;

	list = list->next; // skip to next node.
	int tempPos = 1;
	do {
		if (*min > list->data)
		{
			*min = list->data;
			*pos = tempPos;
		}
		++tempPos;
		list = list->next;
	} while (list != NULL);
}

int returnMinPtr(struct dNode* list, int* min, struct dNode** ptr)
{
	if (list == NULL) return 1; // list is empty.

	// initialize results with first node.
	*min = list->data;
	*ptr = list;

	list = list->next; // skip to next node node.
	do {
		if (*min > list->data)
		{
			*min = list->data;
			*ptr = list;
		}
		list = list->next;
	} while (list != NULL);
}

int returnMaxPos(struct dNode* list, int* max, int* pos)
{
	if (list == NULL) return 1; // list is empty.

	// initialize result with first node.
	*max = list->data;
	*pos = 0;

	list = list->next; // skip to next node.
	int tempPos = 1;
	do {
		if (*max < list->data)
		{
			*max = list->data;
			*pos = tempPos;
		}
		++tempPos;
		list = list->next;
	} while (list != NULL);
}

int returnMaxPtr(struct dNode* list, int* max, struct dNode** ptr)
{
	if (list == NULL) return 1; // list is empty.

	// initialize results with first node.
	*max = list->data;
	*ptr = list;

	list = list->next; // skip to next node node.
	do {
		if (*max < list->data)
		{
			*max = list->data;
			*ptr = list;
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
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

int deleteBeforePos(struct dNode** list, int pos)
{
	if (*list == NULL) return 1; // list is empty.
	if (pos == 0) return -2; // no action needed.

	struct dNode* head = *list; // original head node.
	struct dNode* newHead = NULL; // new head node.
	*list = head->next; // pos == 0 invalid, skip ahead.
	int tempPos = 1;
	while (*list != NULL)
	{
		struct dNode* curr = *list;
		if (tempPos == pos)
		{
			printf("%d\t%p\n\n", curr->data, curr);
			newHead = curr;
			newHead->prev = NULL;
			// reset list, delete nodes before newHead.
			*list = head;
			do {
				struct dNode* dummy = *list;
				*list = dummy->next;
				free(dummy);
			} while (*list != newHead);

			*list = newHead; // reset list to newHead.
			return 0;
		}
		*list = curr->next;
		++tempPos;
	}
	*list = head; // pos not in list, reset list.
	return 1;
}

int deleteAfterPos(struct dNode** list, int pos)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list;
	int tempPos = 0;
	while (*list != NULL)
	{
		struct dNode* curr = *list;
		if (tempPos == pos) // find pos in list.
		{
			if (curr->next == NULL) // pos is last node, no action needed.
			{
				*list = head;
				return -2;
			}

			do {
				struct dNode* dummy = curr->next;
				curr->next = dummy->next;
				free(dummy);
			} while (curr->next != NULL);
			*list = head;
			return 0;
		}
		*list = curr->next;
		++tempPos;
	}
	*list = head; // pos not in list, reset list.
	return 1;
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

int returnFrontData(struct dNode* list, int* data)
{
	if (list == NULL) return 1; // list is empty.
	*data = list->data;
	return 0;
}

int returnBackData(struct dNode* list, int* data)
{
	if (list == NULL) return 1; // list is empty.

	do {
		if (list->next == NULL)
		{
			*data = list->data;
			return 0;
		}
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

int returnTailPos(struct dNode* list, int* pos)
{
	if (list == NULL) return 1; // list is empty.

	*pos = 0;
	do {
		++*pos;
		list = list->next;
	} while (list != NULL);
	return 0;
}

int returnTailPtr(struct dNode* list, struct dNode** ptr)
{
	if (list == NULL) return 1; // list is empty.

	do {
		if (list->next == NULL)
		{
			*ptr = list;
			return 0;
		}
		list = list->next;
	} while (list != NULL);
}

int movePosFront(struct dNode** list, int pos)
{
	if (*list == NULL) return 1; // list is empty.
	if (pos == 0) return -2; // no action needed.

	struct dNode* head = *list;
	*list = head->next; // no action on pos == 0, skip head node.
	int tempPos = 1;

	do {
		struct dNode* curr = *list;
		if(tempPos == pos)
		{
			struct dNode* before = curr->prev;
			struct dNode* after = curr->next;
			if (before != NULL)
			{
				before->next = after;
			}
			if (after != NULL)
			{
				after->prev = before;
			}
			curr->prev = NULL;
			curr->next = head;
			head->prev = curr;
			head = curr;
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != NULL);
	*list = head; // position not in list, reset list.
	return -1;
}

int movePosBack(struct dNode** list, int pos)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list;
	struct dNode* curr = NULL;
	struct dNode* prev = NULL;
	struct dNode* newTail = NULL;
	int tempPos = 0;
	while (*list != NULL)
	{
		curr = *list;
		if (tempPos == pos)
		{
			if (curr->next == NULL) // pos is last node, no action needed.
			{
				*list = head;
				return -2;
			}

			newTail = curr;
			if (pos == 0)
			{
				head = head->next;
				head->prev = NULL;
			}
			else
			{
				prev->next = curr->next;
			}

			// find last node, add newTail after.
			do {
				if (curr->next == NULL)
				{
					curr->next = newTail;
					newTail->prev = curr;
					newTail->next = NULL;
					*list = head;
					return 0;
				}
				curr = curr->next;
			} while (curr != NULL);
		}
		*list = curr->next;
		prev = curr;
		++tempPos;
	}
	*list = head; // pos not in list, reset list.
	return 1;
}

int movePosUp(struct dNode** list, int pos)
{
	if (*list == NULL) return 1; // list is empty.
	if (pos == 0) return -2; // no action needed.

	struct dNode* head = *list;
	struct dNode* before = NULL; // node before previous node.
	struct dNode* prev = head; // previous node in list sweep.
	struct dNode* curr = NULL; // current node in list sweep.
	struct dNode* after = NULL; // node after current node.
	*list = head->next; // pos == 0 invalid, skip ahead.
	int tempPos = 1;
	// find pos in list.
	do {
		curr = *list;
		if (pos == tempPos) // found pos.
		{
			after = curr->next;
			if (prev == head)
			{
				head = curr;
			}
			// swap current/previous nodes.
			if (before != NULL)
			{
				before->next = curr;
			}
			curr->prev = before;
			curr->next = prev;
			prev->prev = curr;
			prev->next = after;
			if (after != NULL)
			{
				after->prev = prev;
			}

			*list = head;
			return 0;
		}
		before = prev;
		prev = curr;
		*list = curr->next;
		++tempPos;
	} while (*list != NULL);
	*list = head; // pos not in list, reset list.
	return 1;
}

int movePosDown(struct dNode** list, int pos)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list;
	struct dNode* before = NULL; // previous node in list sweep.
	struct dNode* curr = NULL; // current node in list sweep.
	struct dNode* next = NULL; // node after current node in list sweep.
	struct dNode* after = NULL; // node after next node in list sweep.
	int tempPos = 0;
	// find pos in list.
	while (*list != NULL)
	{
		curr = *list;
		if (pos == tempPos) // found pos.
		{
			if (curr->next == NULL)
			{
				*list = head; // pos is last node, no action needed.
				return -2;
			}

			next = curr->next;
			after = curr->next->next;
			if (curr == head)
			{
				head = curr->next;
			}

			if (before != NULL)
			{
				before->next = next;
			}
			next->prev = before;
			next->next = curr;
			curr->prev = next;
			curr->next = after;
			if (after != NULL)
			{
				after->prev = curr;
			}

			*list = head;
			return 0;
		}
		before = curr;
		*list = curr->next;
		++tempPos;
	}
	*list = head; // pos not in list, reset list.
	return 1;
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
	printf("\n");
	return 0;
}

int reverse(struct dNode** list)
{
	if (*list == NULL) return 1; // list is empty.

	struct dNode* head = *list; // head node reasigned each iteration.
	struct dNode* tail = *list; // original head is final node when done.
	*list = head->next;

	do {
		struct dNode* curr = *list;
		struct dNode* after = curr->next;
		curr->prev = NULL;
		curr->next = head;
		head->prev = curr;
		tail->next = after;
		if(after != NULL) // check if tail is final node.
		{
			after->prev = tail;
		}
		head = curr;
		*list = tail->next;
	} while (*list != NULL);
	*list = head;
}
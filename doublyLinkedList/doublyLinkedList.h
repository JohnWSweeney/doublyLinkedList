#pragma once
#include <stdio.h>
#include "nodes.h"
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

struct dNode* init(int data);
int addFront(struct dNode** list, int data);
int addBack(struct dNode** list, int data);
int deleteFront(struct dNode** list);
int deleteBack(struct dNode* list);
int clear(struct dNode** list);
int isEmpty(struct dNode* list);
int size(struct dNode* list, int* nodeCount);
int print(struct dNode* list);
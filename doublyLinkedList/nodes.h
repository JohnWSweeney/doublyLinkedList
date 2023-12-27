#pragma once
#include <stdlib.h>

struct dNode
{
	int data;
	struct dNode* next;
	struct dNode* prev;
};
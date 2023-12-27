#pragma once
#include <stdio.h>
//#include <stdlib.h>
#include "nodes.h"

struct dNode* init(int data);
int addBack(struct dNode** list, int data);
int print(struct dNode* list);
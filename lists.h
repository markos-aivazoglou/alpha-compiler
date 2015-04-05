#include <stdio.h>
#include <stdlib.h>
struct list{
	unsigned int label;
	struct list* next;
};

struct list* newlist(unsigned int x);
struct list* merge(struct list* list1, struct list* list2);
void enlist(struct list* list, unsigned int x);
void printlist(const char* t, struct list* list);
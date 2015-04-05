#include "lists.h"

struct list* newlist(unsigned int x){
	struct list* newList = NULL;
	newList =(struct list*) malloc(sizeof(struct list));
	newList->label = x;
	newList->next = NULL;
	return newList;
}

struct list* merge(struct list* list1, struct list* list2){
	if(!list1 && !list2)
		return NULL;
	else if(!list2)
		return list1;
	else if(!list1)
		return list2;
	struct list * temp = NULL;
	temp = list1;
	while(temp->next){
		temp = temp->next;
	}
	temp->next = list2;
	return list1;
}

void enlist(struct list* list, unsigned int x){
	struct list* curr = NULL;
	struct list* temp = NULL;
	curr = list;
	temp = (struct list*)malloc(sizeof(struct list));
	while (curr){
		curr = curr->next;
	}
	temp->label = x;
	temp->next = NULL;
	curr = temp;
}

void printlist(const char* t, struct list* list){
	struct list* temp = NULL;
	temp = list;
	while(temp){
		printf("Stixeio tis %s einai to:%d\n",t,temp->label);
		temp = temp->next;
	}
}
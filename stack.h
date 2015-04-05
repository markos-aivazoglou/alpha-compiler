#include <stdio.h>
#include <assert.h>
#define STACKSIZE 100

unsigned int offsetStack[STACKSIZE];
void offsetPush(unsigned int offset);
unsigned int offsetPop();
int isEmpty();
int isFull();
#include "stack.h"

int top = 0;

void offsetPush(unsigned int offset){
        assert(top<101);
        offsetStack[top++] = offset;
}

unsigned int offsetPop(){
        assert(top<101);
        return offsetStack[--top];
}

int isEmpty(){
	if(top == 0){return 1;}
	else{return 0;}
}

int isFull(){
	if(top==99){return 1;}
	else{return 0;}
}
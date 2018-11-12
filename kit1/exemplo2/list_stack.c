#include <stdlib.h>
#include "stack.h"

typedef struct TCD_Stack
{
	int primeiro;
	struct TCD_Stack* resto;
} TCD_Stack;

TAD_Stack init_stack()
{
	TAD_Stack stack=malloc(sizeof(TCD_Stack));
	stack->primeiro=0;
	stack->resto=NULL;
	return stack;
}

TAD_Stack push_to_stack(TAD_Stack stack,int value)
{
	TAD_Stack s=malloc(sizeof(TCD_Stack));
	s->primeiro=value;
	s->resto=stack;
	return s;
}

int get_value_stack(TAD_Stack stack)
{
	return stack->primeiro;
}

TAD_Stack remove_from_stack(TAD_Stack stack)
{
	TAD_Stack s;
	s=stack->resto;
	free(stack);
	return s;
}

TAD_Stack destroy_stack(TAD_Stack stack)
{
	free(stack);
	stack=NULL;
	return stack;
}
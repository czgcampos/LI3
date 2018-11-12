#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#define SIZE 1000

typedef struct TCD_Stack
{
	int valores[SIZE];
	int tamanho;
} TCD_Stack;

TAD_Stack init_stack()
{
	TAD_Stack stack=malloc(sizeof(TCD_Stack));
	stack->tamanho=0;
	return stack;
}

TAD_Stack push_to_stack(TAD_Stack stack,int value)
{
	if(stack->tamanho<SIZE)
	{
		stack->tamanho=stack->tamanho+1;
		stack->valores[stack->tamanho]=value;
	}

	return stack;
}

int get_value_stack(TAD_Stack stack)
{
	return stack->valores[stack->tamanho];
}

TAD_Stack remove_from_stack(TAD_Stack stack)
{
	if(stack->tamanho>0)
		stack->tamanho--;
	return stack;
}

TAD_Stack destroy_stack(TAD_Stack stack)
{
	free(stack);
	stack=NULL;
	return stack;
}
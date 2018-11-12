#include <stdio.h>
#include "stack.h"

int main(int argc, char* argv[])
{
	TAD_Stack stack = init_stack();
	stack = push_to_stack(stack, 2);
	int res;
	res = get_value_stack(stack);
	printf("%d\n", res);
	stack = remove_from_stack(stack);
	stack = destroy_stack(stack);
	return 0;
}
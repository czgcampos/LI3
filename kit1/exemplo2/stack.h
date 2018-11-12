typedef struct TCD_Stack* TAD_Stack;

TAD_Stack init_stack();
TAD_Stack push_to_stack(TAD_Stack stack,int value); //adiciona valor ao ínicio da stack
int get_value_stack(TAD_Stack stack);	//retorna valor no ínicio da stack
TAD_Stack remove_from_stack(TAD_Stack stack);	//remove valor do ínicio da stack
TAD_Stack destroy_stack(TAD_Stack stack);
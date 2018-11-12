
/*Declaração struct */
typedef struct TCD_Printer* TAD_Printer;

//Tipo concreto de dados TCD
//Tipo abstrato de dados TAD

/*declaração funções */
TAD_Printer init_printer();
TAD_Printer addto_header(TAD_Printer printer, char* new_header);
TAD_Printer print(TAD_Printer printer, char* message);
TAD_Printer destroy_printer(TAD_Printer printer);
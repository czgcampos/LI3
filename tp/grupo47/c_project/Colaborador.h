#include "Parser.h"

typedef struct TCD_colaborador * TAD_colaborador;

TAD_colaborador initColaborador();
TAD_colaborador parseColaborador(TAD_colaborador colaborador, xmlNodePtr cur, xmlDocPtr doc);
char* parseUsername(TAD_colaborador colaborador, xmlNodePtr atu, xmlDocPtr doc);
long parseIdColaborador(TAD_colaborador colaborador, xmlNodePtr atu, xmlDocPtr doc);
long getColaboradorId(TAD_colaborador col);
char* getColaboradorNome(TAD_colaborador col);
TAD_colaborador limpaColaborador(TAD_colaborador colaborador);
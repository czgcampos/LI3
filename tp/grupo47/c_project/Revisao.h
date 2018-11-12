#include "Colaborador.h"

typedef struct TCD_revisao * TAD_revisao;

TAD_revisao initRevisao();
TAD_revisao parseRevisao(TAD_revisao revisao, xmlNodePtr cur, xmlDocPtr doc);
void parseTexto(long* nbytes, long* npalavras, xmlNodePtr atu, xmlDocPtr doc);
long parseIdRevisao(TAD_revisao, xmlNodePtr atu, xmlDocPtr doc);
char* parseIntervaloTempo(TAD_revisao, xmlNodePtr atu, xmlDocPtr doc);
long getRevisaoId(TAD_revisao revisao);
long getNBytes (TAD_revisao revisao);
long getNPalavras (TAD_revisao revisao);
TAD_colaborador getColaborador(TAD_revisao revisao);
char* getIntervaloTempo(TAD_revisao revisao);
TAD_revisao limpaRevisao(TAD_revisao revisao);
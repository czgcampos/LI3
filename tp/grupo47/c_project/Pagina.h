#include "Revisao.h"

typedef struct TCD_pagina * TAD_pagina;

void printpg(TAD_pagina p);
TAD_pagina initPagina();
TAD_pagina parsePagina(TAD_pagina nodo, xmlNodePtr atu, xmlDocPtr doc);
char* parseTituloArtigo(TAD_pagina pagina, xmlNodePtr atu, xmlDocPtr doc);
char* getTitulo(TAD_pagina pagina);
TAD_revisao getRevisao(TAD_pagina pagina);
TAD_pagina limpaPagina(TAD_pagina pagina);
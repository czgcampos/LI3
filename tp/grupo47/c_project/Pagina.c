#include "Pagina.h"

typedef struct TCD_pagina
{
	char* titulo;
	TAD_revisao rev;
} TCD_pagina;

/* Funçao para inicializar a estrutura da pagina */
TAD_pagina initPagina()
{
	TCD_pagina* pag=(TAD_pagina)malloc(sizeof(TCD_pagina));
	pag->titulo=NULL;
	pag->rev=initRevisao();
	return pag;
}

/* Funçao para fazer o parsing do titulo do artigo */
char* parseTituloArtigo(TAD_pagina pagina, xmlNodePtr atu, xmlDocPtr doc)
{
	xmlChar* chave=NULL;
	chave=xmlNodeListGetString(doc,atu->xmlChildrenNode,1);
    pagina->titulo=(char *)malloc((strlen((char *)chave)+1));
    pagina->titulo=strcpy(pagina->titulo,(char *)chave);
    xmlFree(chave);
    return pagina->titulo;
}

/* Funçao para fazer o parsing da pagina, procura as tags do titulo e revisao */
TAD_pagina parsePagina(TAD_pagina pagina, xmlNodePtr atu, xmlDocPtr doc)
{
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	{
		if(!xmlStrcmp(atu->name,(const xmlChar *) "title"))
			pagina->titulo=parseTituloArtigo(pagina,atu,doc);
		if(!xmlStrcmp(atu->name,(const xmlChar *) "revision"))
		{
			pagina->rev=initRevisao();
			pagina->rev=parseRevisao(pagina->rev,atu,doc);
		}
	}
	return pagina;
}

/* Retorna o titulo de uma determinada pagina */
char* getTitulo(TAD_pagina pagina)
{
	if(pagina!=NULL)
		return pagina->titulo;
	else
		return NULL;
}

/* Retorna a revisao de uma determinada pagina */
TAD_revisao getRevisao(TAD_pagina pagina)
{
	if(pagina!=NULL)
		return pagina->rev;
	else
		return NULL;
}

/* Funçao para libertar a memoria alocada para estrutura TAD_pagina */
TAD_pagina limpaPagina(TAD_pagina pagina)
{
	if(pagina!=NULL)
	{
		free(pagina->titulo);
		pagina->rev=limpaRevisao(pagina->rev);
		free(pagina);
		pagina=NULL;
	}
	return pagina;
}
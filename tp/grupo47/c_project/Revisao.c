#include "Revisao.h"

typedef struct TCD_revisao
{
	long id;
	char* data;
	long nbytes;
	long npalavras;
	TAD_colaborador colab;
} TCD_revisao;

/* Funçao para inicializar a estrutura da revisao */
TAD_revisao initRevisao()
{
	TAD_revisao rev=(TAD_revisao)malloc(sizeof(TCD_revisao));
	rev->id=0L;
	rev->data=NULL;
	rev->nbytes=0L;
	rev->npalavras=0L;
	rev->colab=initColaborador();
	return rev;
}
/* Funçao auxiliar para contar o numero de palavras num determinado texto de uma revisao */
long contaPalarvas(char* texto)
{
	int m;
	long c=0;
	for (m=0; texto[m]; m++)
		if ((texto[m]==' ' || texto[m]=='\n' || texto[m]=='\t') && (texto[m+1]!=' ' && texto[m+1]!='\n' && texto[m+1]!='\t'))
			c++;
	return c;
}

/* Funçao para fazer o parsing do id de uma determinada revisao */
long parseIdRevisao(TAD_revisao revisao, xmlNodePtr atu, xmlDocPtr doc)
{
	xmlChar *chave=NULL;
	chave=xmlNodeListGetString(doc,atu->xmlChildrenNode,1);
	revisao->id=atol((char *)chave);
	xmlFree(chave);
	return revisao->id;
}

/* Funçao para fazer o parsing da data de uma determinada revisao */
char* parseIntervaloTempo(TAD_revisao revisao, xmlNodePtr atu, xmlDocPtr doc)
{
	xmlChar *chave=NULL;
	chave=xmlNodeListGetString(doc,atu->xmlChildrenNode,1);
    revisao->data=(char *)malloc(strlen((char *)chave)+1);
    revisao->data=strcpy(revisao->data,(char *)chave);
    xmlFree(chave);
	return revisao->data;
}

/* Funçao para fazer o parsing do texto de uma determinada revisao */
void parseTexto(long* nbytes, long* npalavras, xmlNodePtr atu, xmlDocPtr doc)
{
	xmlChar* chave=NULL;
	chave=xmlNodeListGetString(doc,atu->xmlChildrenNode,1);
	if(chave!=NULL)
	{
		*nbytes=strlen((char*)chave);
		*npalavras=contaPalarvas((char*)chave);
		xmlFree(chave);
	}
}

/* Funçao para fazer o parsing da revisao, procura as tags id, timestamp, text e contributor */
TAD_revisao parseRevisao(TAD_revisao revisao, xmlNodePtr atu, xmlDocPtr doc)
{
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	{
		if(!xmlStrcmp(atu->name,(const xmlChar *) "id"))
			revisao->id=parseIdRevisao(revisao,atu,doc);
		if(!xmlStrcmp(atu->name,(const xmlChar *) "timestamp"))
			revisao->data=parseIntervaloTempo(revisao,atu,doc);
		if(!xmlStrcmp(atu->name,(const xmlChar *) "text"))
			parseTexto(&revisao->nbytes,&revisao->npalavras,atu,doc);
		if(!xmlStrcmp(atu->name,(const xmlChar *) "contributor"))
		{
			revisao->colab=initColaborador();
			revisao->colab=parseColaborador(revisao->colab,atu,doc);
		}
	}
	return revisao;
}

/* Funçao que retorna o id de uma determinada revisao */
long getRevisaoId(TAD_revisao revisao)
{
	if(revisao!=NULL)
		return revisao->id;
	else
		return 0L;
}

/* Funçao que retorna o numero de bytes do texto de uma determinada revisao */
long getNBytes (TAD_revisao revisao) 
{
	if (revisao!=NULL)
		return revisao->nbytes;
	else return 0L;
}

/* Funçao que retorna o numero de palavras do texto de uma determinada revisao */
long getNPalavras (TAD_revisao revisao) {
	if (revisao!=NULL) {
		return revisao->npalavras;
	}
	else return 0L;
}

/* Funçao que retorna o colaborador que efetuou uma determinada revisao */
TAD_colaborador getColaborador(TAD_revisao revisao)
{
	return revisao->colab;
}

/* Funçao que retorna a data de uma determinada revisao */
char* getIntervaloTempo(TAD_revisao revisao)
{
	if(revisao!=NULL)
		return revisao->data;
	else
		return NULL;
}

/* Funçao que liberta a memoria alocada para a estrutura TAD_revisao revisao */
TAD_revisao limpaRevisao(TAD_revisao revisao)
{
	if(revisao!=NULL)
	{
		free(revisao->data);
		revisao->colab=limpaColaborador(revisao->colab);
		free(revisao);
		revisao=NULL;
	}
	return revisao;
}
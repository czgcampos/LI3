#include "Colaborador.h"

typedef struct TCD_colaborador
{
	long id;
	char* username;
} TCD_colaborador;

/* Funçao para inicializar a estrutura do colaborador */
TAD_colaborador initColaborador()
{
	TAD_colaborador col=(TAD_colaborador)malloc(sizeof(TCD_colaborador));
	col->id=0;
	col->username=NULL;
	return col;
}

/* Funçao para fazer o parsing do username do colaborador */
char* parseUsername(TAD_colaborador colaborador, xmlNodePtr atu, xmlDocPtr doc)
{
	xmlChar *chave=NULL;
	chave=xmlNodeListGetString(doc,atu->xmlChildrenNode,1);
    colaborador->username=(char *)malloc(strlen((char *)chave)+1);
    colaborador->username=strcpy(colaborador->username,(char *)chave);
    xmlFree(chave);
    return colaborador->username;
}

/* Funçao para fazer o parsing do id do colaborador */
long parseIdColaborador(TAD_colaborador colaborador, xmlNodePtr atu, xmlDocPtr doc)
{
	xmlChar *chave=NULL;
	chave=xmlNodeListGetString(doc,atu->xmlChildrenNode,1);
	colaborador->id=atol((char *)chave);
	xmlFree(chave);
	return colaborador->id;
}

/* Funçao para fazer o parsing do colaborador, procura pela tag do username e id */
TAD_colaborador parseColaborador(TAD_colaborador colaborador, xmlNodePtr atu, xmlDocPtr doc)
{
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	{
		if(!xmlStrcmp(atu->name,(const xmlChar *) "username"))
			colaborador->username=parseUsername(colaborador,atu,doc);
		if(!xmlStrcmp(atu->name,(const xmlChar *) "id"))
			colaborador->id=parseIdColaborador(colaborador,atu,doc);
	}
	return colaborador;
}

/* Funçao para retornar o id de um determinado colaborador, retorna 0 caso TAD_colaborador esteja a NULL*/
long getColaboradorId(TAD_colaborador col)
{
	if(col!=NULL) 
		return col->id;
	else 
		return 0L;
}

/* Funçao para retornar o nome de um determinado colaborador, caso nao encontre retorna NULL */
char* getColaboradorNome(TAD_colaborador col)
{
	if (col!=NULL) 
		return col->username;
	else 
		return NULL;
}

/* Funçao para libertar a memoria alocada a estrutura TAD_colaborador */
TAD_colaborador limpaColaborador(TAD_colaborador colaborador)
{
	if(colaborador!=NULL)
	{
		free(colaborador->username);
		free(colaborador);
		colaborador=NULL;
	}
	return colaborador;
}
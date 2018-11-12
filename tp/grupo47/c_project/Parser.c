#include "Parser.h"

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag username */
xmlNodePtr apontaUtilizador(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "contributor"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "username"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag id de um com colaborador */
xmlNodePtr apontaIdColaborador(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "contributor"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu=atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "id"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag colaborador de uma revisao */
xmlNodePtr apontaColaborador(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "revision"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "contributor"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag texto de uma revisao */
xmlNodePtr apontaTexto(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "revision"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu=atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "text"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag data de uma revisao*/
xmlNodePtr apontaIntervaloTempo(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "revision"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "timestamp"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag id de uma revisao */
xmlNodePtr apontaIdRevisao(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "revision"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu=atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "id"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag revision de uma pagina */
xmlNodePtr apontaRevisao(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "page"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "revision"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag id de uma pagina */
xmlNodePtr apontaIdArtigo(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "page"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "id"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag titulo de uma pagina */
xmlNodePtr apontaTituloArtigo(xmlNodePtr atu)
{
	if(xmlStrcmp(atu->name,(const xmlChar *) "page"))
		return NULL;
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu = atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "title"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer a apontar para um local onde exista a tag pagina */
xmlNodePtr apontaPagina(xmlNodePtr atu)
{
	for(atu=atu->xmlChildrenNode;atu!=NULL;atu=atu->next)
	    if(!xmlStrcmp(atu->name,(const xmlChar *) "page"))
	    	return atu;
    return NULL;
}

/* Funçao que coloca o xmlNodePointer na raiz caso encontre a tag mediawiki */
xmlNodePtr parseRaiz(xmlNodePtr atu, xmlDocPtr doc)
{
	atu=xmlDocGetRootElement(doc);
	if(atu==NULL)
	{
		imprime("Documento vazio\n");
		xmlFreeDoc(doc);
		return NULL;
	}
	if(xmlStrcmp(atu->name,(const xmlChar *) "mediawiki"))
	{
		imprime("Documento de tipo errado, nodo raiz != mediawiki.");
		xmlFreeDoc(doc);
	}
	return atu;
}
/* Funçao que coloca o xmlDocPointer no inicio do documento */
xmlDocPtr parseDoc(char *nomedoc, xmlNodePtr atu, xmlDocPtr doc)
{
	doc=xmlParseFile(nomedoc);
	if(doc==NULL)
	{
		imprime("Parser falhou!\n");
		return NULL;
	}
	return doc;
}
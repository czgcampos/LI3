#include "interface.h"

typedef struct TCD_istruct
{
	TAD_artigos artigos;
	long numeroArtigos;
	long numeroArtigosUnicos;
	long numeroRevisoes;
	TAD_colaboradores colaboradores;
} TCD_istruct;

TAD_istruct init()
{
	TAD_istruct mystruct=(TAD_istruct)malloc(sizeof(TCD_istruct));
	mystruct->artigos=NULL;
	mystruct->numeroArtigos=0L;
	mystruct->numeroArtigosUnicos=0L;
	mystruct->numeroRevisoes=0L;
	mystruct->colaboradores=NULL;
	return mystruct;
}

TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[])
{
	imprime("Aguarde enquanto o carregamento e efetuado...");
	if(qs==NULL)
		qs=init();
	xmlDocPtr doc=NULL;
	xmlNodePtr atu=NULL;
	int i;
	for(i=0;i<nsnaps;i++)
	{
		doc=parseDoc(snaps_paths[i],atu,doc);
		if(doc==NULL)
			break;
		atu=parseRaiz(atu,doc);
		if(atu==NULL)
			break;
		qs->artigos=carregaArtigos(atu,qs->artigos,doc);
		xmlFree(doc);
		xmlFree(atu);
	}
	qs->numeroArtigos=contaArtigos(qs->artigos);
	qs->numeroArtigosUnicos=contaArtigosUnicos(qs->artigos);
	qs->numeroRevisoes=qs->numeroArtigos-contaRevisoesRepetidas(qs->artigos);
	qs->colaboradores=ordena(artigosToColaboradores(qs->artigos,qs->colaboradores));
	return qs;
}

long all_articles(TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	return qs->numeroArtigos;
}

long unique_articles(TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	return qs->numeroArtigosUnicos;
}

long all_revisions(TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	return qs->numeroRevisoes;
}

long* top_10_contributors(TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	long* res=(long*)malloc(sizeof(long)*10);
	return top10Contribuidores(qs->colaboradores,res);
}

char* contributor_name(long contributor_id, TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	return existeColab(qs->artigos,contributor_id);
}

long* top_20_largest_articles(TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	long* ids=(long*)malloc(sizeof(long)*20);
	long* nbytes=(long*)malloc(sizeof(long)*20);
	return top20ArtigosBytes(qs->artigos,ids,nbytes);
}

char* article_title(long article_id, TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	return procuraTitulo(article_id,qs->artigos);
}

long* top_N_articles_with_more_words(int n, TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	long* ids=(long*)malloc(sizeof(long)*n);
	long* npalavras=(long*)malloc(sizeof(long)*n);
	return topNArtigosPalavras(qs->artigos,ids,npalavras,n);
}

int funcaoComparacao(const void *a, const void *b) 
{
    const char** ia=(const char **)a;
    const char** ib=(const char **)b;
    return strcmp(*ia, *ib);
} 

char** titles_with_prefix(char* prefix, TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	int tam=0;
	char** array=(char**)malloc(sizeof(array));
	array=titulosComPrefixo(array,prefix,qs->artigos,&tam);
	qsort(array, tam, sizeof(char *), funcaoComparacao);
	array[tam]=NULL;
	return array;
}

char* article_timestamp(long article_id, long revision_id, TAD_istruct qs)
{
	if(qs->numeroArtigos==0)
		imprime("Necessita fazer load, estrutura de dados vazia!");
	return procuraIntervalo(article_id,revision_id,qs->artigos);
}

TAD_istruct clean(TAD_istruct qs)
{
	if(qs!=NULL)
	{
		if(qs->artigos!=NULL)
		{
			qs->artigos=limpaArtigos(qs->artigos);
			qs->colaboradores=limpaColaboradores(qs->colaboradores);
		}
		free(qs);
		qs=NULL;
	}
	imprime("Meta dados apagados");
	return qs;
}
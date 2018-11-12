#include "Artigos.h"

typedef struct TCD_paginas* TAD_paginas;

typedef struct TCD_artigos
{
	long id;
    TAD_paginas paginas;
    TAD_artigos esq;
    TAD_artigos dir;
    int altura;
} TCD_artigos;

typedef struct TCD_paginas
{
    TAD_pagina cabeca;
    TAD_paginas prox;
}TCD_paginas;

/* Funçao para alocar um novo artigo a estrutura dos artigos TCD_artigos */
TAD_artigos novoArtigo(long idArtigo, xmlNodePtr atu, xmlDocPtr doc)
{
    TAD_artigos artigo=(TAD_artigos)malloc(sizeof(TCD_artigos));
    artigo->id=idArtigo;
    artigo->paginas=(TAD_paginas)malloc(sizeof(TCD_paginas));
    artigo->paginas->cabeca=initPagina();
    artigo->paginas->cabeca=parsePagina(artigo->paginas->cabeca,atu,doc);
    artigo->paginas->prox=NULL;
    artigo->esq=NULL;
    artigo->dir=NULL;
    artigo->altura=1;
    return artigo;
}

/* Funçao para alocar uma nova pagina a estrutura dos artigos TCD_artigos */
TAD_artigos novaPagina(xmlNodePtr atu, xmlDocPtr doc, TAD_artigos artigos)
{
    TAD_paginas nova=(TAD_paginas)malloc(sizeof(TCD_paginas));
    nova->cabeca=initPagina();
    nova->cabeca=parsePagina(nova->cabeca,atu,doc);
    nova->prox=artigos->paginas;
    artigos->paginas=nova;
    return artigos;
}

/* Funçao auxiliar para o calculo do maximo entre dois inteiros */
int maximo(int a, int b)
{
    return (a>b)?a:b;
}

/* Funçao para calcular a altura de uma arvore de artigos */
int altura(TAD_artigos artigos)
{
    if(artigos==NULL)
        return 0;
    return artigos->altura;
}
/* Funçao de rotaçao a direita da arvore */
TAD_artigos rodaDireita(TAD_artigos artigos)
{
    TAD_artigos aux1=artigos->esq;
    TAD_artigos aux2=aux1->dir;
    aux1->dir=artigos;
    artigos->esq=aux2;
    artigos->altura=maximo(altura(artigos->esq),altura(artigos->dir))+1;
    aux1->altura=maximo(altura(aux1->esq),altura(aux1->dir))+1;
    return aux1;
}

/* Funçao de rotaçao a esquerda da arvore */
TAD_artigos rodaEsquerda(TAD_artigos artigos)
{
    TAD_artigos aux1=artigos->dir;
    TAD_artigos aux2=aux1->esq;
    aux1->esq=artigos;
    artigos->dir=aux2;
    artigos->altura=maximo(altura(artigos->esq),altura(artigos->dir))+1;
    aux1->altura=maximo(altura(aux1->esq),altura(aux1->dir))+1;
    return aux1;
}

/* Funçao para calcular o fator de balanceamento da arvore, de forma a mante-la sempre balanceada */
int fatorBalanceamento(TAD_artigos artigos)
{
    if(artigos==NULL)
        return 0;
    return altura(artigos->esq)-altura(artigos->dir);
}

/* Funçao para a inserçao de um novo artigo */
TAD_artigos insereArtigo(TAD_artigos artigos, long id, xmlDocPtr doc, xmlNodePtr atu)
{
    if(artigos==NULL)
        return novoArtigo(id,atu,doc);
    if(id<artigos->id)
        artigos->esq=insereArtigo(artigos->esq,id,doc,atu);
    else if(id>artigos->id)
        artigos->dir=insereArtigo(artigos->dir,id,doc,atu);
    else
        return novaPagina(atu,doc,artigos);
    artigos->altura=1+maximo(altura(artigos->esq),altura(artigos->dir));
    int fator=fatorBalanceamento(artigos);
    if(fator>1 && id<artigos->esq->id)
        return rodaDireita(artigos);
    if(fator<-1 && id>artigos->dir->id)
        return rodaEsquerda(artigos);
    if(fator>1 && id>artigos->esq->id)
    {
        artigos->esq=rodaEsquerda(artigos->esq);
        return rodaDireita(artigos);
    }
    if(fator<-1 && id<artigos->dir->id)
    {
        artigos->dir=rodaDireita(artigos->dir);
        return rodaEsquerda(artigos);
    }
    return artigos;
}

/* Funçao para fazer o parsing do id de um artigo */
long parseIdArtigo(long id, xmlNodePtr atu, xmlDocPtr doc)
{
    xmlChar *chave=NULL;
    chave=xmlNodeListGetString(doc,atu->xmlChildrenNode,1);
    id=atol((char *)chave);
    xmlFree(chave);
    return id;
}

/* Funçao para o carregamento da estrutura dos artigos */
TAD_artigos carregaArtigos(xmlNodePtr atu, TAD_artigos artigos, xmlDocPtr doc)
{
    long id=0L;
    xmlNodePtr aux=NULL;
	for(atu=apontaPagina(atu);atu!=NULL;atu=atu->next)
    {
        if(!xmlStrcmp(atu->name,(const xmlChar *) "page"))
        {
            aux=apontaIdArtigo(atu);
            id=parseIdArtigo(id,aux,doc);
            artigos=insereArtigo(artigos,id,doc,atu);
        }
    }
	return artigos;
}

long contaArtigos(TAD_artigos artigos)
{
    long res=0L;
    if(artigos!=NULL)
    {
        TAD_paginas aux=artigos->paginas;
        for(;aux!=NULL;aux=aux->prox,res++);
        res+=contaArtigos(artigos->esq)+contaArtigos(artigos->dir);
    }
    return res;
}

long contaArtigosUnicos(TAD_artigos artigos)
{
    long res=0L;
    if(artigos!=NULL) 
        res+=1+contaArtigosUnicos(artigos->esq)+contaArtigosUnicos(artigos->dir);
    return res;
}
/* Funçao para calcular o numero de revisoes repetidas para auxiliar no calculo da query 3 */
long contaRevisoesRepetidas(TAD_artigos artigos)
{
    long res=0L;
    if(artigos!=NULL)
    {
        TAD_paginas aux=artigos->paginas;
        if(aux!=NULL)
        {
            TAD_revisao rev1=NULL, rev2=NULL;
            for(;aux->prox!=NULL;aux=aux->prox)
            {
                rev1=getRevisao(aux->cabeca);
                rev2=getRevisao(aux->prox->cabeca);
                if(getRevisaoId(rev1)==getRevisaoId(rev2))
                    res++;
            }
        }
        res+=contaRevisoesRepetidas(artigos->esq)+contaRevisoesRepetidas(artigos->dir);
    }
    return res;
}

TAD_colaboradores artigosToColaboradores(TAD_artigos artigos, TAD_colaboradores colabs)
{   
    if (artigos!=NULL)
    {
        long idr=0L;
        long idc=0L;
        TAD_paginas aux=artigos->paginas;
        TAD_colaborador colab=NULL;
        TAD_revisao revisao=NULL;
        for(;aux!=NULL;aux=aux->prox)
        {
            revisao=getRevisao(aux->cabeca);
            idr=getRevisaoId(revisao);
            colab=getColaborador(revisao);
            idc=getColaboradorId(colab);
            if(idc!=0L)
                colabs=insereColaboradores(colabs,idr,idc);
        }
        colabs=artigosToColaboradores(artigos->esq,colabs);
        colabs=artigosToColaboradores(artigos->dir,colabs); 
    }
    return colabs;
}

/* Funçao de procura do id de um determinado colaborador na arvore dos artigos */
/* Retorna NULL caso não encontre nada */
char* existeColab(TAD_artigos artigos, long idColaborador)
{
    if(artigos!=NULL)
    {
        long id=0;
        TAD_paginas aux=artigos->paginas;
        TAD_revisao revisao=NULL;
        TAD_colaborador colab=NULL;
        for(;aux!=NULL;aux=aux->prox) 
        {
            revisao=getRevisao(aux->cabeca);
            colab=getColaborador(revisao);
            id=getColaboradorId(colab);
            if(id==idColaborador)
            {
                return getColaboradorNome(colab);
            }
        }
        char* resesq=existeColab(artigos->esq,idColaborador);
        if(resesq!=NULL)
            return resesq;
        char* resdir=existeColab(artigos->dir,idColaborador);
        if(resdir!=NULL) 
            return resdir;
    }
    return NULL;
}

long* top20ArtigosBytes(TAD_artigos artigos,long* ids, long* nbytes) 
{
    if(artigos!=NULL)
    {
        int inserir=0, i;
        TAD_paginas aux=artigos->paginas;
        TAD_revisao revisao=getRevisao(aux->cabeca);
        long bytes=getNBytes(revisao);
        long idtmp=artigos->id;
        for(;aux!=NULL;aux=aux->prox)
        {
            revisao=getRevisao(aux->cabeca);
            if(getNBytes(revisao)>bytes)
                bytes=getNBytes(revisao);
        }
        for(i=19;i>0 && ((nbytes[i-1]<bytes) || (nbytes[i-1]==bytes && ids[i-1]>idtmp));i--)
        {
            nbytes[i]=nbytes[i-1];
            ids[i]=ids[i-1];
            inserir=1;
        }
        if(inserir)
        {
            nbytes[i]=bytes;
            ids[i]=idtmp;
        }
        ids=top20ArtigosBytes(artigos->esq,ids,nbytes);
        ids=top20ArtigosBytes(artigos->dir,ids,nbytes);
    }
    return ids;
}

long* topNArtigosPalavras(TAD_artigos artigos,long* ids, long* npalavras, int tam) 
{
    if(artigos!=NULL)
    {
        int inserir=0, i;
        TAD_paginas aux=artigos->paginas;
        TAD_revisao revisao=getRevisao(aux->cabeca);
        long palavras=getNPalavras(revisao);
        long idtmp=artigos->id;
        for(;aux!=NULL;aux=aux->prox)
        {
            revisao=getRevisao(aux->cabeca);
            if(getNPalavras(revisao)>palavras)
                palavras=getNPalavras(revisao);
        }
        for(i=tam-1;i>0 && ((npalavras[i-1]<palavras) || (npalavras[i-1]==palavras && ids[i-1]>idtmp));i--)
        {
            npalavras[i]=npalavras[i-1];
            ids[i]=ids[i-1];
            inserir=1;
        }
        if(inserir)
        {
            npalavras[i]=palavras;
            ids[i]=idtmp;
        }
        ids=topNArtigosPalavras(artigos->esq,ids,npalavras,tam);
        ids=topNArtigosPalavras(artigos->dir,ids,npalavras,tam);
    }
    return ids;
}

char* procuraTitulo(long idArtigo, TAD_artigos artigos)
{
    char* res=NULL;
    if(artigos!=NULL)
    {
        if(idArtigo==artigos->id && artigos->paginas!=NULL)
            return getTitulo(artigos->paginas->cabeca);
        else if(idArtigo>artigos->id)
            res=procuraTitulo(idArtigo,artigos->dir);
        else
            res=procuraTitulo(idArtigo,artigos->esq);
    }
    return res;
}

char** titulosComPrefixo(char** array, char* pre, TAD_artigos artigos, int* tam) 
{   
    if(artigos!=NULL)
    {
        if(artigos->paginas!=NULL)
        {
            char* titulo=getTitulo(artigos->paginas->cabeca);
            if (!strncmp(pre,titulo,strlen(pre)))
            {
                array=(char**)realloc(array,sizeof(array)*((*tam)+2));
                array[*tam]=(char*)malloc(strlen(titulo)+1);
                array[*tam]=strcpy(array[*tam],titulo);
                *tam=*tam+1;
            }
        }
        array=titulosComPrefixo(array,pre,artigos->esq,tam);
        array=titulosComPrefixo(array,pre,artigos->dir,tam);
    }
    return array;
}

char* procuraIntervalo(long idArtigo, long idRevisao, TAD_artigos artigos)
{
    char* res=NULL;
    if(artigos!=NULL)
    {
        if(idArtigo==artigos->id)
        {
            TAD_paginas aux=artigos->paginas;
            TAD_revisao revisao=NULL;
            for(;aux!=NULL;aux=aux->prox)
            {
                revisao=getRevisao(aux->cabeca);
                if(revisao!=NULL && getRevisaoId(revisao)==idRevisao)
                    return getIntervaloTempo(revisao);
            }
        }
        else if(idArtigo>artigos->id)
            res=procuraIntervalo(idArtigo,idRevisao,artigos->dir);
        else
            res=procuraIntervalo(idArtigo,idRevisao,artigos->esq);
    }
    return res;
}

/* Funçao para libertar a memoria alocada para a estrutura TAD_artigos */
TAD_artigos limpaArtigos(TAD_artigos artigos)
{
	if(artigos!=NULL)
    {
        TAD_paginas aux=artigos->paginas;
        for(;aux!=NULL;aux=aux->prox)
        {
            aux->cabeca=limpaPagina(aux->cabeca);
            free(aux);
        }
        artigos->esq=limpaArtigos(artigos->esq);
        artigos->dir=limpaArtigos(artigos->dir);
        free(artigos);
        artigos=NULL;
    }
    return artigos;
}
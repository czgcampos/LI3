#include "Colaboradores.h"

typedef struct TCD_ids* TAD_ids;

typedef struct TCD_ids
{
    long idRevisao;
    TAD_ids esq;
    TAD_ids dir;
} TCD_ids;

typedef struct TCD_colaboradores
{
    long idColab;
    int contribuicoes;
    TAD_ids ids;
    TAD_colaboradores prox;
} TCD_colaboradores;

TAD_ids novoId(TAD_ids ids, long idr)
{
    ids=(TAD_ids)malloc(sizeof(TCD_ids));
    ids->idRevisao=idr;
    ids->esq=NULL;
    ids->dir=NULL;
    return ids;
}

/* Funçao para criar um novo TAD_colaborador na lista de colaboradores */
/* Devolve a lista de colaboradores */
TAD_colaboradores novoColaborador(TAD_colaboradores colaboradores,long idr, long idc)
{
    colaboradores=(TAD_colaboradores)malloc(sizeof(TCD_colaboradores));
    colaboradores->idColab=idc;
    colaboradores->contribuicoes=1;
    colaboradores->ids=novoId(colaboradores->ids,idr);
    colaboradores->prox=NULL;
    return colaboradores;
}

/* Esta funçao insere um TAD_colaborador na lista ligada de TAD_colaboradores */
/* Retorna a nova lista, com o colaborador inserido */
TAD_ids insereRevCol(TAD_ids e, long idr)
{
    if(e==NULL)
    {
        e=novoId(e,idr);
        return e;
    }
    else
    {
        if(idr<e->idRevisao)
            e->esq=insereRevCol(e->esq,idr);
        else if(idr>e->idRevisao)
            e->dir=insereRevCol(e->dir,idr);
    }
    return e;
}

/* Funçao de carregamento da lista de colaboradores */
/* Retorna a lista de colaboradores */
TAD_colaboradores insereColaboradores(TAD_colaboradores colaboradores, long idrev, long idcol)
{
    if(colaboradores==NULL)
    {   
        colaboradores=novoColaborador(colaboradores,idrev,idcol);
        return colaboradores;
    }
    TAD_colaboradores aux=NULL;
    for(aux=colaboradores;aux->prox!=NULL;aux=aux->prox)
    {
        if(idcol==aux->idColab)
        {
            TAD_ids auxel = aux->ids;
            if(idrev < auxel->idRevisao)
            {
                auxel->esq=insereRevCol(auxel->esq,idrev);
                aux->contribuicoes=aux->contribuicoes+1;
                return colaboradores;
            }
            else if(idrev>auxel->idRevisao)
            {
                auxel->dir=insereRevCol(auxel->dir,idrev);
                aux->contribuicoes=aux->contribuicoes+1;
                return colaboradores;
            }
            else
                return colaboradores;
        }
    }
    aux->prox=novoColaborador(colaboradores,idrev,idcol);
    return colaboradores;
}

int tamanhoRevisoes(TAD_ids i)
{
    if(i!=NULL)
        return 1+tamanhoRevisoes(i->esq)+tamanhoRevisoes(i->dir);
    else return 0;
}

/* Funçao de ordenaçao da lista de colaboradores pelo numero de contribuiçoes de cada um */
TAD_colaboradores ordena(TAD_colaboradores lista)
{
    if (lista == NULL || lista->prox == NULL)
        return lista;
    TAD_colaboradores atual=lista;
    TAD_colaboradores ant=lista;
    TAD_colaboradores maior=lista;
    TAD_colaboradores maiorant=lista;
    while (atual != NULL)
    {
        if (tamanhoRevisoes(atual->ids)>tamanhoRevisoes(maior->ids))
        {
            maiorant = ant;
            maior = atual;
        }
        else if (tamanhoRevisoes(atual->ids)==tamanhoRevisoes(maior->ids) && atual->idColab<maior->idColab)
        {
            maiorant = ant;
            maior = atual;
        }        
        ant = atual;
        atual = atual->prox;
    }
    TAD_colaboradores tmp = NULL;
    if (maior != lista)
    {
        maiorant->prox=lista;
        tmp = lista->prox;
        lista->prox = maior->prox;
        maior->prox = tmp;
    }
    maior->prox=ordena(maior->prox);
    return maior;
}

long* top10Contribuidores(TAD_colaboradores c, long* res)
{
    int i;
    for(i=0;c!=NULL && i<10;i++,c=c->prox)
        res[i]=c->idColab;
    return res;
}

TAD_ids limpaIds(TAD_ids ids)
{
    if(ids!=NULL)
    {
        ids->esq=limpaIds(ids->esq);
        ids->dir=limpaIds(ids->dir);
        free(ids);
        ids=NULL;
    }
    return ids;
}

/* Funçao para libertar a memoria alocada para estrutura TAD_colaboradores */
TAD_colaboradores limpaColaboradores(TAD_colaboradores colaboradores)
{
    if(colaboradores!=NULL)
    {
        TAD_colaboradores aux=colaboradores;
        for(;aux!=NULL;aux=aux->prox)
        {
            aux->ids=limpaIds(aux->ids);
            free(aux);
        }
        free(colaboradores);
        colaboradores=NULL;
    }
    return colaboradores;
}
#include "Pagina.h"
#include "Colaboradores.h"

typedef struct TCD_artigos* TAD_artigos;

TAD_artigos carregaArtigos(xmlNodePtr cur, TAD_artigos artigos, xmlDocPtr doc);
long parseIdArtigo(long id, xmlNodePtr atu, xmlDocPtr doc);
long contaArtigos(TAD_artigos artigos);
long contaArtigosUnicos(TAD_artigos artigos);
long contaRevisoesRepetidas(TAD_artigos artigos);
TAD_colaboradores artigosToColaboradores(TAD_artigos artigos, TAD_colaboradores colabs);
char* existeColab(TAD_artigos artigos, long idColaborador);
long* top20ArtigosBytes(TAD_artigos artigos, long* ids, long* nbytes);
char* procuraTitulo(long idArtigo, TAD_artigos artigos);
long* topNArtigosPalavras(TAD_artigos artigos,long* ids, long* npalavras, int tam);
char** titulosComPrefixo(char** res,char* prefixo,TAD_artigos artigos,int* c);
char* procuraIntervalo(long idArtigo,long idRevisao, TAD_artigos artigos);
TAD_artigos limpaArtigos(TAD_artigos artigos);
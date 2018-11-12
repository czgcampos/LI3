#include "interface.h"
#include "Menu.h"

int main()
{
	char enter='a', opcao='0';
	int nsnaps=0;
	char** snaps_paths=NULL;
	char** prefixotmp=NULL;
	long res=0L, idArtigo=0L, idRevisao=0L;
	char* aux=NULL;
	long* top10=NULL;
	long* top20=NULL;
	long* topN=NULL;
	TAD_istruct mystruct=init();
	do
	{
		menuInicial(); opcao=getOpcao();
		switch(opcao)
		{
			case 'l':
			case 'L': nsnaps=quantosSnaps(); snaps_paths=caminhoSnaps(nsnaps);
					mystruct=load(mystruct,nsnaps,snaps_paths);
					imprime("Operação de carregamento terminada!"); 
					pausa(0,enter,1); break;
			case 'a':
			case 'A': mystruct=clean(mystruct); pausa(0,enter,1); break;
			case '0': res=all_articles(mystruct); imprimeL(res); 
					pausa(0,enter,1); break;
			case '1': res=unique_articles(mystruct); imprimeL(res); 
					pausa(0,enter,1); break;
			case '2': res=all_revisions(mystruct); imprimeL(res); 
					pausa(0,enter,1); break;
			case '3': top10=top_10_contributors(mystruct);
					imprime("Lista dos 10 Colaboradores com mais contribuições:");
					imprimeListaLong(top10,10); pausa(0,enter,1); break;
			case '4': imprime("Digite um id de Colaborador.");
					res=lerLong(); aux=contributor_name(res,mystruct);
					imprime(aux); pausa(0,enter,1); break;
			case '5': top20=top_20_largest_articles(mystruct);
					imprime("Lista dos 20 artigos com mais bytes:");
					imprimeListaLong(top20,20); pausa(0,enter,1); break;
			case '6': imprime("Digite um id de artigo."); idArtigo=lerLong();
					aux=article_title(idArtigo,mystruct); imprime(aux);
					pausa(0,enter,1); break;
			case '7': imprime("Digite o numero de artigos."); nsnaps=lerInt();
					topN=top_N_articles_with_more_words(nsnaps,mystruct);
					imprime("Lista dos N artigos com mais palavras:");
					imprimeListaLong(topN,nsnaps); pausa(0,enter,1); break;
			case '8': imprime("Digite um prefixo."); aux=lerString();
					prefixotmp=titles_with_prefix(aux,mystruct);
					imprimeLista(prefixotmp); pausa(0,enter,1); break;
			case '9': imprime("Digite um id de artigo."); idArtigo=lerLong();
					imprime("Digite um id de revisao."); idRevisao=lerLong();
					aux=article_timestamp(idArtigo,idRevisao,mystruct); imprime(aux); 
					pausa(0,enter,1); break;
			case 's':
			case 'S': opcao='s'; break;
			default: imprime("Escolha invalida!"); pausa(0,enter,1);
		}
	} while(opcao!='s');
	mystruct=clean(mystruct);
	return 0;
}
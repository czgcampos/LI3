#include "Menu.h"

char getOpcao()
{
	char res='0';
    do
    {
        printf("Escolha uma opção. ");
        scanf(" %c",&res);
    }
    while(!isdigit(res) && res!='S' && res!='s' && res!='A' && res!='a' && res!='L' && res!='l');
    return res;
}

void menuInicial()
{
    system("clear");
    printf("+------------------------------------------+\n");
	printf("|         Gestão de Wikipedia              |\n");
    printf("+------------------------------------------+\n");
    printf("| L/l. Ler os metadados.                   |\n");
    printf("+------------------------------------------+\n");
    printf("| A/a. Apagar os metadados.                |\n");
    printf("+------------------------------------------+\n");
    printf("| 0. Numero total de artigos.              |\n");
    printf("+------------------------------------------+\n");
    printf("| 1. Numero total de artigos unicos.       |\n");
    printf("+------------------------------------------+\n");
    printf("| 2. Numero total de revisões.             |\n");
    printf("+------------------------------------------+\n");
    printf("| 3. Top 10 colaboradores.                 |\n");
    printf("+------------------------------------------+\n");
    printf("| 4. Colaborador com um dado id.           |\n");    
    printf("+------------------------------------------+\n");
    printf("| 5. Top 20 artigos mais longos.           |\n");
    printf("+------------------------------------------+\n");
    printf("| 6. Titulo de um dado artigo.             |\n");
    printf("+------------------------------------------+\n");
    printf("| 7. Top N artigos com mais palavras.      |\n");
    printf("+------------------------------------------+\n");
    printf("| 8. Lista de titulos com um dado prefixo. |\n");
    printf("+------------------------------------------+\n");
    printf("| 9. Data de uma dada revisão.             |\n");
    printf("+------------------------------------------+\n");
    printf("| S/s. Sair.                               |\n");
    printf("+------------------------------------------+\n\n");
}

int quantosSnaps()
{
    int res=0;
    do
    {
        printf("Quantos backups deseja carregar? ");
        scanf(" %d",&res);
    } while(res<0 || res>12);
    return res;
}

char** caminhoSnaps(int nsnaps)
{
    char** res = (char **)malloc(nsnaps+1);
    char* caminho=(char *)malloc(100);
    int i;
    for(i=0;i<nsnaps;i++)
    {
        printf("Qual o caminho para o %dº snapshot? ", i+1);
        scanf("%s",caminho);
        res[i]=(char *)malloc(strlen(caminho));
        res[i]=strcpy(res[i],caminho);
    }
    res[i]=NULL;
    return res;
}

void pausa(int stdin, char enter, int quantos)
{
    printf("Prima <Enter>\n"); 
    read(stdin,&enter,quantos);
}

void imprime(char* mensagem)
{
    if(mensagem==NULL)
        printf("NULL\n");
    else
        printf("%s\n", mensagem);
    return;
}

void imprimeL(long res)
{
    printf("%ld\n", res);
    return;
}

char* lerString()
{
    char* aux=(char *)malloc(100);
    scanf("%s",aux);
    char* res=(char *)malloc(strlen(aux));
    res=strcpy(res,aux);
    free(aux);
    return res;
}

void imprimeLista(char** lista)
{
    if(lista!=NULL)
    {
        int i;
        for(i=0;lista[i]!=NULL;i++)
            printf("%s\n", lista[i]);
    }
}

void imprimeListaLong(long* res, int tam)
{
    int i;
    printf("-----------------\n");
    for(i=0;i<tam;i++)
    {
        printf("|%2d +%10ld |\n", i+1,*(res+i));
        printf("+---+-----------+\n");
    }
}

long lerLong()
{
    long aux=0L;
    scanf("%ld",&aux);
    return aux;
}

int lerInt()
{
    int aux=0;
    scanf("%d",&aux);
    return aux;
}

void liberta(char** caminhos)
{
    int i;
    if(caminhos!=NULL)
    {
        for(i=0;caminhos[i]!=NULL;i++)
            free(caminhos[i]);    
        free(caminhos);
    }
}
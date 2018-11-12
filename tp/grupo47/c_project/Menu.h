#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

void menuInicial();
char getOpcao();
int quantosSnaps();
char** caminhoSnaps(int nsnaps);
void imprime(char* mensagem);
void imprimeL(long res);
void pausa(int stdin, char enter, int quantos);
char* lerString();
void imprimeLista(char** lista);
void imprimeListaLong(long* res, int tam);
long lerLong();
int lerInt();
void liberta(char** caminhos);
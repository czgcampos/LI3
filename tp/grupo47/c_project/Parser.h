#include "Menu.h"

xmlDocPtr parseDoc(char *nomedoc, xmlNodePtr atu, xmlDocPtr doc);
xmlNodePtr parseRaiz(xmlNodePtr atu, xmlDocPtr doc);
xmlNodePtr apontaPagina(xmlNodePtr atu);
xmlNodePtr apontaIdArtigo(xmlNodePtr atu);
xmlNodePtr apontaUsername(xmlNodePtr atu);
xmlNodePtr apontaIdColaborador(xmlNodePtr atu);
xmlNodePtr apontaColaborador(xmlNodePtr atu);
xmlNodePtr apontaTexto(xmlNodePtr atu);
xmlNodePtr apontaIntervaloTempo(xmlNodePtr atu);
xmlNodePtr apontaIdRevisao(xmlNodePtr atu);
xmlNodePtr apontaRevisao(xmlNodePtr atu);
xmlNodePtr apontaTituloArtigo(xmlNodePtr atu);
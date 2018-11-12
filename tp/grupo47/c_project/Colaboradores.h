#include "Colaborador.h"

typedef struct TCD_colaboradores* TAD_colaboradores;

TAD_colaboradores insereColaboradores(TAD_colaboradores colaboradores, long idrev, long idcol);
TAD_colaboradores ordena(TAD_colaboradores lista);
long* top10Contribuidores(TAD_colaboradores colab, long* res);
TAD_colaboradores limpaColaboradores(TAD_colaboradores colaboradores);
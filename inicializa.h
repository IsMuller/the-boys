#ifndef INICIALIZA
#define INICIALIZA

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_INVASOES (T_FIM_DO_MUNDO / 10000)

#include "entidades.h"

struct mundo *inicializa_mundo();//inicializa o mundo, utilizando todas as funcoes anteriores

struct mundo *destroi_mundo(); //destroi o mundo, encerrando o programa

#endif
#ifndef INICIALIZA
#define INICIALIZA

#define T_INICIO 0
#define T_FIM_DO_MUNDO 60 * 24 * 30//525600 // 525600 = 60*24*365 = 365 dias
#define N_TAMANHO_MUNDO 1000//20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_INVASOES (T_FIM_DO_MUNDO / 10000)

#include "entidades.h"

void eventos_iniciais(struct mundo *w); //coloca na LEF os eventos iniciais para começar a simulaçao

struct mundo *inicializa_mundo();//inicializa o mundo, utilizando todas as funcoes anteriores

struct mundo *destroi_mundo(); //destroi o mundo, encerrando o programa

#endif
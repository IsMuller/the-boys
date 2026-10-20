#ifndef INICIALIZA
#define INICIALIZA

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600 // 525600 = 60*24*365 = 365 dias
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_INVASOES (T_FIM_DO_MUNDO / 10000)

#include "entidades.h"

void inicializa_heroi(struct heroi *h, int id);//inicializa um heroi a partir de seu id

void inicializa_base(struct base *b, int id);//inicializa uma base a partir de seu id

void inicializa_missao(struct missao *m, int id);//inicializa uma missao a partir de seu id

void inicializa_invasao(struct invasao *i, int id);//inicializa uma invasao a partir de seu id

struct mundo *inicializa_mundo();//inicializa o mundo, utilizando todas as funcoes anteriores

#endif
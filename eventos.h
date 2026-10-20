#ifndef EVENTOS
#define EVENTOS

#include "entidades.h"


void evento_chega (int tempo, struct heroi *h, struct base *b);

void evento_espera(int tempo, struct heroi *h, struct base *b);

void evento_desiste(int tempo, struct heroi *h, struct base *b);

void evento_avisa(int tempo, struct base *b);

void evento_entra(int tempo, struct heroi *h, struct base *b);

void evento_sai(int tempo, struct heroi *h, struct base *b);

void evento_viaja(int tempo, struct heroi *h, struct base *b);

void evento_morre(int tempo, struct heroi *h, struct base *b);

void evento_missao(int tempo, struct missao *m);

void evento_invade(int tempo, struct invasao *i, struct base *b);

void evento_recupera_heroi(int tempo, struct heroi *h);

void evento_reconstroi_base(int tempo, struct base *b);

void evento_fim(int tempo);

#endif

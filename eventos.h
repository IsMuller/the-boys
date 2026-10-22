#ifndef EVENTOS
#define EVENTOS
#define EV_CHEGA 0 //precisamos definir uma enumeracao para sabermos o tipo do evento (usamos isso para inserir na LEF)
#define EV_ESPERA 1
#define EV_DESISTE 2
#define EV_AVISA 3
#define EV_ENTRA 4
#define EV_SAI 5
#define EV_VIAJA 6
#define EV_MORRE 7
#define EV_MISSAO 8
#define EV_INVADE 9
#define EV_RECUPERA_HEROI 10
#define EV_RECONSTROI_BASE 11
#define EV_FIM 12
#include "entidades.h"

struct evento { //usamos para armazenar os dados na LEF
    int tipo; //tipo da base, de 0 a 12
    int tempo; //tempo que o evento ocorre
    struct heroi *heroi; //heroi envolvido (se tiver)  ---> se nao tiver, valor é NULL
    struct base *base; //base envolvida (se tiver)
    struct missao *missao; //missao envolvida (se tiver)
    struct invasao *invasao; //invasao envolvida (se tiver)
};

void evento_chega (struct mundo *w, struct heroi *h, struct base *b);

void evento_espera(struct mundo *w, struct heroi *h, struct base *b);

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

#include "eventos.h"
#include "entidades.h"

void evento_chega (struct mundo *w, struct heroi *h, struct base *b){
    int espera;
    h -> base = b -> id;
    if (cjto_card (b -> equipe) < b -> max && fila_tamanho(b -> f_espera) == 0)
        espera = 1;
    else    
        espera = (h -> paciencia) > (10 * fila_tamanho(b -> f_espera));

    if (espera && b -> estado == 1){
        struct evento *ev = malloc (sizeof(struct evento));
        if (!ev)
            return;
        ev -> tipo = EV_ESPERA;
        ev -> tempo = w -> min_atual;
        ev -> heroi = h;
        ev -> base = b; 
        ev -> missao = NULL;
        ev -> invasao = NULL;
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    }
    else {
        struct evento *ev = malloc (sizeof(struct evento));
        if (!ev)
            return;
        ev -> tipo = EV_DESISTE;
        ev -> tempo = w -> min_atual;
        ev -> heroi = h;
        ev -> base = b; 
        ev -> missao = NULL;
        ev -> invasao = NULL;
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    }
}

void evento_espera(struct mundo *w, struct heroi *h, struct base *b){
    
    fila_insere(b -> f_espera, h);
    struct evento *ev = malloc (sizeof(struct evento));
    if (!ev)
        return;
    ev -> tipo = EV_AVISA;
    ev -> tempo = w -> min_atual;
    ev -> heroi = NULL;
    ev -> base = b; 
    ev -> missao = NULL;
    ev -> invasao = NULL;
    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);

}

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

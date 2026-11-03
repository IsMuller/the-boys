#include <stdlib.h>
#include "simulacao.h"
#include "eventos.h"
#include "fprio.h"

void simula_mundo(struct mundo *w){
    
    struct evento *prim_ev;
    int tipo; //tipo do prim ev
    int tempo; //tempo do prim ev

    int fim = 0; //quando o fim acontecer, fim = 1
    while (!fim){
        prim_ev = fprio_retira(w -> lef, &tipo, &tempo);
        w -> min_atual = tempo;
        switch (prim_ev -> tipo){
            case EV_CHEGA:
                evento_chega(w, w -> herois[prim_ev -> id1], w -> bases[prim_ev -> id2]);
                break;

            case EV_ESPERA:
                evento_espera(w, w -> herois[prim_ev -> id1], w -> bases[prim_ev -> id2]);
                break;

            case EV_DESISTE:
                evento_desiste(w, w -> herois[prim_ev -> id1], w -> bases[prim_ev -> id2]);
                break;
            
            case EV_AVISA:
                evento_avisa(w, w -> bases[prim_ev -> id1]);
                break;
        
            case EV_ENTRA:
                evento_entra(w, w -> herois[prim_ev -> id1], w -> bases[prim_ev -> id2]);
                break;

            case EV_SAI:
                evento_sai(w, w -> herois[prim_ev -> id1], w -> bases[prim_ev -> id2]);
                break;

            case EV_VIAJA:
                evento_viaja(w, w -> herois[prim_ev -> id1], w -> bases[prim_ev -> id2]);
                break;

            case EV_MORRE:
                evento_morre(w, w -> herois[prim_ev -> id1], w -> bases[prim_ev -> id2]);
                break;

            case EV_MISSAO:
                evento_missao(w, w -> missoes[prim_ev -> id1]);
                break;

            case EV_INVADE:
                evento_invade(w, w -> invasoes[prim_ev -> id1],  w -> bases[prim_ev -> id2]);
                break;

            case EV_RECUPERA_HEROI:
                evento_recupera_heroi(w, w -> herois[prim_ev -> id1]);
                break;

            case EV_RECONSTROI_BASE:
                evento_reconstroi_base(w, w -> bases[prim_ev -> id1]);
                break;

            case EV_FIM:
                evento_fim(w);
                fim = 1;
                break;
        }
        
        free(prim_ev);
        w -> n_eventos_tratados++;
    }
}

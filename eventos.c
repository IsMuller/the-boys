#include <stdlib.h>
#include <stdio.h>
#include "inicializa.h"
#include "eventos.h"
#include "entidades.h"
#include "conjunto.h"
#include "funcoes_extras.h"


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
        ev -> id1 = h -> id;
        ev -> id2 = b -> id; 
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", w -> min_atual, h -> id, b -> id, cjto_card (b -> equipe), b -> max);
    }
    else {
        struct evento *ev = malloc (sizeof(struct evento));
        if (!ev)
            return;
        ev -> tipo = EV_DESISTE;
        ev -> tempo = w -> min_atual;
        ev -> id1 = h -> id;
        ev -> id2 = b -> id; 
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", w -> min_atual, h -> id, b -> id, cjto_card (b -> equipe), b -> max);

        
    }
}

void evento_espera(struct mundo *w, struct heroi *h, struct base *b){

    fila_insere(b -> f_espera, &h -> id);
    if (fila_tamanho(b -> f_espera) > b -> f_max) //vai atualizando a quantidade max de pessoas q ja ficaram na fila
        b -> f_max = fila_tamanho(b -> f_espera);

    struct evento *ev = malloc (sizeof(struct evento));
    if (!ev)
        return;
    ev -> tipo = EV_AVISA;
    ev -> tempo = w -> min_atual;
    ev -> id1 = b -> id; 
    ev -> id2 = -1;
    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", w -> min_atual, h -> id, b -> id, fila_tamanho (b -> f_espera) - 1);

    
}

void evento_desiste(struct mundo *w, struct heroi *h, struct base *b) {

    struct evento *ev = malloc (sizeof(struct evento));
    if (!ev)
        return;

    int id_nova_base = aleat(0, w -> n_bases - 1); //achamos um novo id aleatorio de base

    ev -> tipo = EV_VIAJA;
    ev -> tempo = w -> min_atual;
    ev -> id1 = h -> id;
    ev -> id2 = id_nova_base; 

    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    printf("%6d: DESISTE HEROI %2d BASE %d\n", w -> min_atual, h -> id, b -> id);

    
}

void evento_avisa(struct mundo *w, struct base *b) {

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", w -> min_atual, b -> id, cjto_card (b -> equipe), b -> max);
    fila_imprime (b -> f_espera);
    printf(" ]\n");
    
    while (cjto_card(b -> equipe) < b -> max && fila_tamanho(b -> f_espera) > 0) {

        struct evento *ev = malloc (sizeof(struct evento));
        if (!ev)
            return; 

        struct heroi *primh = fila_retira (b -> f_espera); //retira e retorna o primeiro heroi
        cjto_insere (b -> equipe, primh -> id); //insere o id do prim da fila na base
        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", w -> min_atual, b -> id, primh -> id);

        ev -> tipo = EV_ENTRA;
        ev -> tempo = w -> min_atual;
        ev -> id1 = primh -> id;
        ev -> id2 = b -> id;
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    }   
}

void evento_entra(struct mundo *w, struct heroi *h, struct base *b){

    struct evento *ev = malloc (sizeof(struct evento));
    if (!ev)
        return; 

    int tpb = 15 + h -> paciencia * aleat(1, 20);

    ev -> tipo = EV_SAI;
    ev -> tempo = w -> min_atual + tpb;
    ev -> id1 = h -> id;
    ev -> id2 = b -> id;
    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", w -> min_atual, h -> id, b -> id, cjto_card (b -> equipe), b -> max, w -> min_atual + tpb);
}

void evento_sai(struct mundo *w, struct heroi *h, struct base *b){

    if (!cjto_pertence(b -> equipe, h -> id)) { //garante que, se ocorrer a invasao e o heroi ja foi embora, nao processa sua "saida" antiga
        return; 
    }

    cjto_retira (b -> equipe, h -> id);
    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", w -> min_atual, h -> id, b -> id, cjto_card (b -> equipe), b -> max);

    int id_nova_base = aleat(0, w -> n_bases - 1); //achamos um novo id aleatorio de base

    struct evento *ev1 = malloc (sizeof(struct evento));
    
    ev1 -> tipo = EV_VIAJA;
    ev1 -> tempo = w -> min_atual;
    ev1 -> id1 = h -> id;
    ev1 -> id2 = id_nova_base;

    fprio_insere(w -> lef, ev1, ev1 -> tipo, ev1 -> tempo); //insere evento viaja

    struct evento *ev2 = malloc (sizeof(struct evento));
    
    ev2 -> tipo = EV_AVISA;
    ev2 -> tempo = w -> min_atual;
    ev2 -> id1 = b -> id;
    ev2 -> id2 = -1;

    fprio_insere(w -> lef, ev2, ev2 -> tipo, ev2 -> tempo); //insere evento avisa
}

void evento_viaja(struct mundo *w, struct heroi *h, struct base *b){

    
    struct base *base_atual = w -> bases[h -> base];
    double distancia = distancia_cartesiana(base_atual -> local_base, b -> local_base);
    int duracao = distancia / h -> velocidade;

    struct evento *ev = malloc (sizeof(struct evento));
    if (!ev)
        return;

    ev -> tipo = EV_CHEGA;
    ev -> tempo = w -> min_atual + duracao;
    ev -> id1 = h -> id;
    ev -> id2 = b -> id; 

    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", w -> min_atual, h -> id, base_atual -> id, b -> id, (int) distancia, h -> velocidade, w -> min_atual + duracao);
}

void remove_eventos(struct mundo *w, struct heroi *h, int so_sai){ //remove tanto os evs do h morto (quando so sai = 0) quanto apenas o ev sai no invade (so sai = 1)

    struct fprio_t *lef_temp = fprio_cria ();
    
    int tipo;  //tipo do primeiro evento da lef
    int tempo; //tempo do primeiro evento da lef
    struct evento *prim_ev; 


    while ((prim_ev = fprio_retira(w -> lef, &tipo, &tempo)) != NULL) {

        struct evento *ev = prim_ev;
    
        if (ev -> id1 == h -> id && (ev -> tipo == EV_ENTRA || (!so_sai && (ev -> tipo == EV_SAI
            || ev -> tipo == EV_VIAJA || ev -> tipo == EV_CHEGA || ev -> tipo == EV_ESPERA 
            || ev -> tipo == EV_DESISTE || ev -> tipo == EV_RECUPERA_HEROI)))) //ev entra tambem precisa ser removido em h morto, entao so executa se ambas as condicoes macro forem verdade
           
            free(ev);
        else
            fprio_insere(lef_temp, ev, ev -> tipo, ev -> tempo);
    }

    //apos removido todos os eventos, vamos devolver os elementos para a lef original

    while ((prim_ev = fprio_retira(lef_temp, &tipo, &tempo)) != NULL) 
        fprio_insere(w -> lef, prim_ev, prim_ev -> tipo, prim_ev -> tempo);

    fprio_destroi(lef_temp);
}

void evento_morre(struct mundo *w, struct heroi *h, struct base *b){

    cjto_retira (b -> equipe, h -> id);
    h -> morto = 1;

    remove_eventos(w, h, 0); //remove todos os eventos futuros que tinham o h morto

    struct evento *ev = malloc (sizeof(struct evento));
    
    ev -> tipo = EV_AVISA;
    ev -> tempo = w -> min_atual;
    ev -> id1 = b -> id;
    ev -> id2 = -1;

    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);  
}

void evento_missao(struct mundo *w, struct missao *m){

    struct base **base_dist =  malloc(w -> n_bases * sizeof(struct base *));
    base_dist[0] = w -> bases[0];

    struct base *bmp = NULL; //inicializando a base ativa e apta mais proxima

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", w -> min_atual, m -> id, m -> tentativas);
    cjto_imprime(m -> hab_necessarias);
    printf(" ]\n");

    for(int i = 1; i < w -> n_bases; i++){

        base_dist[i] = w -> bases[i];
        double dist = distancia_cartesiana(base_dist[i] -> local_base, m -> local_missao);

        for(int j = i; j > 0; j--) {

            double menor_dist = distancia_cartesiana(base_dist[j-1] -> local_base, m -> local_missao); 
            if (dist < menor_dist){
                struct base *aux = base_dist[j - 1];
                base_dist[j - 1] = base_dist[j];
                base_dist[j] = aux;

            }
            else   
                break;
        }
    }

    for(int i = 0; i < w -> n_bases; i++){ //passando por todo o vetor de distancias para encontrar a bmp

        double dist = distancia_cartesiana(base_dist[i] -> local_base, m -> local_missao);

        printf("%6d: MISSAO %d BASE %d DIST %.0f HEROIS [ ", w -> min_atual, m -> id, base_dist[i] -> id, dist); //msg de depuracao
        cjto_imprime(base_dist[i] -> equipe);
        printf(" ]\n");

        struct cjto_t *hab_base = cjto_cria (N_HABILIDADES); //num max de habilidades do mundo

        for (int j = 0; j < w -> n_herois; j++){ //vejo se índice do heroi j esta em b e adiciono sua habilidade em hab_base
            if (cjto_pertence(base_dist[i] -> equipe, j) && w -> herois[j] -> estado == 1) {

                printf("%6d: MISSAO %d HAB HEROI %2d: [ ", w -> min_atual, m -> id, j); //msg de depuracao
                cjto_imprime(w -> herois[j] -> habilidades);
                printf(" ]\n");

                struct cjto_t *aux = cjto_uniao (hab_base, w -> herois[j] -> habilidades);
                cjto_destroi(hab_base); //esvazia o antigo hab_base
                hab_base = aux;
            }
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", w -> min_atual, m -> id, base_dist[i] -> id); //msg de depuracao
        cjto_imprime(hab_base);
        printf(" ]\n");

        int eh_bmp = (base_dist[i] -> estado == 1 && cjto_contem (hab_base, m -> hab_necessarias)); //candidata a bmp
        cjto_destroi(hab_base);
        if (eh_bmp) { 
            bmp = base_dist[i];
            break;
        }
    }
   
    free(base_dist);

    if (bmp) {
        w -> n_missoes_cumpridas ++;
        bmp -> missoes ++;
        struct cjto_t *hab_bmp = cjto_cria(N_HABILIDADES); //vamos criar esse conjunto para sabermos q habilidades temos na bmp
        for (int j = 0; j < w -> n_herois; j++) {
            if (cjto_pertence(bmp -> equipe, w -> herois[j] -> id)  && w -> herois[j] -> estado == 1) {
                struct cjto_t *aux_bmp = cjto_uniao(hab_bmp, w->herois[j] -> habilidades);
                cjto_destroi(hab_bmp);
                hab_bmp = aux_bmp;
            }
        }

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", w -> min_atual, m -> id, bmp -> id);
        cjto_imprime(hab_bmp);
        printf(" ]\n");
        cjto_destroi(hab_bmp);

        for (int i = 0; i < w -> n_herois; i++) {//vamos ver como ficaram os herois apos a missao
            if (w -> herois[i] -> estado == 1 && cjto_pertence (bmp -> equipe, w -> herois[i] -> id)){
                double risco = m -> perigo / (w -> herois[i] -> paciencia + w -> herois[i] -> experiencia + 1.0);
                if (risco > aleat(0, 30)) {
                    struct evento *ev = malloc (sizeof(struct evento));
                    ev -> tipo = EV_MORRE;
                    ev -> tempo = w -> min_atual;
                    ev -> id1 = i;
                    ev -> id2 = bmp -> id;

                    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
                    printf("%6d: MORRE HEROI %2d MISSAO %d\n", w -> min_atual,  w -> herois[i] -> id, m -> id);
                }
                else    
                    w -> herois[i] -> experiencia ++;
            }
        }
    }
    else {
        printf("%6d: MISSAO %d IMPOSSIVEL\n", w -> min_atual, m -> id);
        struct evento *ev = malloc (sizeof(struct evento));
        ev -> tipo = EV_MISSAO;
        ev -> tempo = w -> min_atual + 24*60;
        ev -> id1 = m -> id;
        ev -> id2 = -1;
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
        m -> tentativas++;
    } 
}

void evento_invade(struct mundo *w, struct invasao *i, struct base *b){

    if( b -> estado == 1){
        printf("%6d: INVADE BASE %d INVADE %d\n", w -> min_atual, b -> id, i -> id);

         for (int j = 0; j < w -> n_herois; j++) {
            if (cjto_pertence (b -> equipe, w -> herois[j] -> id)){
                w -> herois[j] -> estado = 0;
                struct evento *ev1 = malloc (sizeof(struct evento));
                if (!ev1)
                    return; 
                ev1 -> tipo = EV_RECUPERA_HEROI;
                ev1 -> tempo = w -> min_atual + i -> t_penalidade_heroi;
                ev1 -> id1 = j;
                ev1 -> id2 = -1;
                fprio_insere(w -> lef, ev1, ev1 -> tipo, ev1 -> tempo);

                remove_eventos(w, w -> herois[j], 1); //so sai é verdade

                struct evento *ev2 = malloc (sizeof(struct evento));
                if (!ev2)
                    return; 
                ev2 -> tipo = EV_SAI;
                ev2 -> tempo = w -> min_atual;
                ev2 -> id1 = j;
                ev2 -> id2 = b -> id;
                fprio_insere(w -> lef, ev2, ev2 -> tipo, ev2 -> tempo); 

            }
         }

        printf("%6d: INVADE %d BASE %2d HEROIS INATIVOS [ ", w -> min_atual, i -> id, b -> id);
        cjto_imprime(b -> equipe);
        printf(" ]\n");
        
        w -> n_invasoes_realizadas++;
        
        b -> estado = 0;

        printf("%6d: INVADE %d BASE %d INATIVA\n", w -> min_atual, i -> id, b -> id);

        struct evento *ev3 = malloc (sizeof(struct evento));
        if (!ev3)
            return; 

        ev3 -> tipo = EV_RECONSTROI_BASE;
        ev3 -> tempo = w -> min_atual + i -> t_penalidade_base;
        ev3 -> id1 = b -> id;
        ev3 -> id2 = -1;
        fprio_insere(w -> lef, ev3, ev3 -> tipo, ev3 -> tempo);   
    }
}

void evento_recupera_heroi(struct mundo *w, struct heroi *h){
    w -> herois[h -> id] -> estado = 1;
    
}

void evento_reconstroi_base(struct mundo *w, struct base *b){
     w -> bases[b -> id] -> estado = 1;
     
}

void evento_fim(struct mundo *w){

    printf("%6d: FIM\n", w -> min_atual);
    int quant_mortos = 0;
    //impressao dos herois
    for (int i = 0; i < w -> n_herois; i++){
        if (w -> herois[i] -> morto == 0)
            printf ("HEROI %2d VIVO ", w -> herois[i] -> id);
        else { 
            printf("HEROI %2d MORTO ", w -> herois[i] -> id);
            quant_mortos++;
        }
        printf("PAC %3d VEL %4d EXP %4d HABS [ ", w -> herois[i]-> paciencia, w -> herois[i] -> velocidade, w -> herois[i] -> experiencia);
        cjto_imprime(w -> herois[i] -> habilidades);
        printf(" ]\n");
    }
    float mortalidade = 100.0 * quant_mortos / w -> n_herois;

    for (int i = 0; i < w -> n_bases; i++){
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", w -> bases[i]-> id, w -> bases[i] -> max, w -> bases[i] -> f_max,  w -> bases[i] -> missoes);
    }

    float porcentagem_m_cumpridas = 100.0 *  w -> n_missoes_cumpridas / w -> n_missoes;
    float porcentagem_i_feitas = 100.0 * w -> n_invasoes_realizadas / w -> n_invasoes;

    int min_tentativas_missoes = w -> missoes[0] -> tentativas;
    int max_tentativas_missoes = w -> missoes[0] -> tentativas;
    float soma_tentativas = 0.0;
    //vamos calcular o max e min de tentativas das missoes 
    for (int i = 0; i < w -> n_missoes; i++){
        soma_tentativas += w -> missoes[i] -> tentativas;
        if (w -> missoes[i] -> tentativas < min_tentativas_missoes)
            min_tentativas_missoes = w -> missoes[i] -> tentativas;
        else if (w -> missoes[i] -> tentativas > max_tentativas_missoes)
            max_tentativas_missoes = w -> missoes[i] -> tentativas;
    }

    float media_tentativa_missoes = soma_tentativas / w -> n_missoes;

    printf("EVENTOS TRATADOS: %d\n", w -> n_eventos_tratados);
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", w -> n_missoes_cumpridas, w -> n_missoes, porcentagem_m_cumpridas);
    printf("INVASOES REALIZADAS: %d/%d (%.1f%%)\n", w -> n_invasoes_realizadas, w -> n_invasoes, porcentagem_i_feitas);
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min_tentativas_missoes, max_tentativas_missoes, media_tentativa_missoes);
    printf("TAXA MORTALIDADE: %.1f%%\n", mortalidade);

}
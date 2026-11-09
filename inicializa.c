#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_extras.h"
#include "entidades.h"
#include "inicializa.h"
#include "conjunto.h"
#include "fila.h"
#include "eventos.h"


void inicializa_heroi(struct heroi *h, int id) {//inicializa um heroi a partir de seu id 
    int quant_habilidades;
    h -> id = id;
    h -> morto = 0;
    h -> estado = 1;
    h -> experiencia = 0;
    h -> paciencia = aleat(0, 100);
    h -> velocidade = aleat(50, 5000);
    quant_habilidades = aleat(1, 3);
    h -> habilidades = cjto_aleat(quant_habilidades, N_HABILIDADES); //cria um conjunto de n habilidades aleatorias
}

void inicializa_base(struct base *b, int id) {//inicializa uma base a partir de seu id
    b -> id = id;
    b -> estado = 1;
    b -> missoes = 0;
    b -> local_base = malloc(sizeof(struct localizacao));
    b -> local_base -> x = aleat(0, N_TAMANHO_MUNDO - 1);
    b -> local_base -> y = aleat(0, N_TAMANHO_MUNDO - 1);
    b -> max = aleat(3, 10);
    b -> f_max = 0;
    b -> equipe = cjto_cria(N_HEROIS); //recebe até o valor do id max de herois
    b -> f_espera = fila_cria();
}

void inicializa_missao(struct missao *m, int id) {//inicializa uma missao a partir de seu id
    int quant_habilidades;
    m -> id = id;
    m -> tentativas = 1;
    m -> local_missao = malloc(sizeof(struct localizacao));
    m -> local_missao -> x = aleat(0, N_TAMANHO_MUNDO - 1);
    m-> local_missao -> y = aleat(0, N_TAMANHO_MUNDO - 1);
    quant_habilidades = aleat(6, 10);
    m -> hab_necessarias = cjto_aleat(quant_habilidades, N_HABILIDADES);
    m -> perigo = aleat(0, 100);
}

void inicializa_invasao(struct invasao *i, int id) {//inicializa uma invasao a partir de seu id
    i -> id = id;
    i -> id_base = aleat(0, N_BASES - 1);
    i -> t_penalidade_heroi= aleat(0, 4320);
    i -> t_penalidade_base = aleat(0, 7200);
}

void eventos_iniciais(struct mundo *w){

    int base_ini_id;
    int tempo;

    //criando os eventos iniciais para cada heroi
    for (int i = 0; i < w -> n_herois; i++){

        struct evento *ev = malloc (sizeof(struct evento));
        if (!ev)
            return;

        base_ini_id = aleat(0, w -> n_bases - 1);
        tempo = aleat(0, 4320);
        ev -> tipo = EV_CHEGA;
        ev -> tempo = tempo;
        ev -> id1 = i;
        ev -> id2 = base_ini_id;
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    
    }
    //criando os eventos iniciais de cada missao
    for (int i = 0; i < w -> n_missoes; i++){

        tempo = aleat(0, T_FIM_DO_MUNDO);

        struct evento *ev = malloc (sizeof(struct evento));
        if (!ev)
            return;
        
        ev -> tipo = EV_MISSAO;
        ev -> tempo = tempo;
        ev -> id1 = i;
        ev -> id2 = -1;
        
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    }

    //criando eventos iniciais para cada invasao

    for (int i = 0; i < w -> n_invasoes; i++){

        tempo = aleat((60*24*3) + 1, T_FIM_DO_MUNDO);

        struct evento *ev = malloc (sizeof(struct evento));
        if (!ev)
            return;
        
        ev -> tipo = EV_INVADE;
        ev -> tempo = tempo;
        ev -> id1 = i;
        ev -> id2 = w -> invasoes[i] -> id_base;
        
        fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
    }

    //criando evento FIM
    struct evento *ev = malloc (sizeof(struct evento));

    if (!ev)
         return;

    ev -> tipo = EV_FIM;     
    ev -> tempo = T_FIM_DO_MUNDO;
    ev -> id1 = -1;
    ev -> id2 = -1;

    fprio_insere(w -> lef, ev, ev -> tipo, ev -> tempo);
}


struct mundo *inicializa_mundo(){//inicializa o mundo, utilizando as funcoes anteriores

    struct mundo *w = calloc(1, sizeof(struct mundo)); //uso do calloc pois assim garanto que reservo 1 espaço do tamanho do mundo em que tudo esta zerado

    srand(0);//srand(time(NULL));

    w -> min_atual = T_INICIO;

    w -> tam_mundo = malloc(sizeof(struct localizacao)); //alocando tamanho do mundo

    if (!w -> tam_mundo) {
        free(w);
        return NULL;
    }

    w -> tam_mundo -> x = N_TAMANHO_MUNDO;
    w -> tam_mundo -> y = N_TAMANHO_MUNDO;

    w -> lef = fprio_cria(); //criando LEF
    w -> n_habilidades = N_HABILIDADES;

    //criando os herois
    w -> n_herois = N_HEROIS;
    w -> herois =  malloc(w -> n_herois * sizeof(struct heroi *)); //alocando espaço para o vetor de ponteiros
    if (!w -> herois)
        return NULL;

    for (int i = 0; i < w -> n_herois; i++){
        w -> herois[i] = malloc(sizeof(struct heroi));//alocando cada heroi
        if (!w -> herois[i])
            return NULL;
        inicializa_heroi(w -> herois[i], i);
    }

    //criando as bases
    w -> n_bases = N_BASES;
    w -> bases =  malloc(w -> n_bases * sizeof(struct base *)); //alocando espaço para o vetor de ponteiros
    for (int i = 0; i < w -> n_bases; i++){
        w -> bases[i] = malloc(sizeof(struct base));//alocando cada base
        if (!w -> bases[i])
            return NULL;
        inicializa_base(w -> bases[i], i);
    }

    //criando as missoes
    w -> n_missoes = N_MISSOES;
    w -> n_missoes_cumpridas = 0;
    w -> missoes =  malloc(w -> n_missoes * sizeof(struct missao *)); //alocando espaço para o vetor de ponteiros
    for (int i = 0; i < w -> n_missoes; i++){
        w -> missoes[i] = malloc(sizeof(struct missao));//alocando cada missao
        if (!w -> missoes[i])
            return NULL;
        inicializa_missao(w -> missoes[i], i);
    }

    //criando as invasoes
    w -> n_invasoes = N_INVASOES;
    w -> invasoes =  malloc(w -> n_invasoes * sizeof(struct invasao *)); //alocando espaço para o vetor de ponteiros
    for (int i = 0; i < w -> n_invasoes; i++){
        w -> invasoes[i] = malloc(sizeof(struct invasao));//alocando cada missao
        if (!w -> invasoes[i])
            return NULL;
        inicializa_invasao(w -> invasoes[i], i);
    }
    
    // criando eventos iniciais e os inserindo na LEF
    eventos_iniciais(w);
    return w;
}

struct mundo *destroi_mundo(struct mundo *w) { //destroi o mundo, encerrando o programa   

    //liberando herois
    for(int i = 0; i < w -> n_herois; i++){

        cjto_destroi(w -> herois[i] -> habilidades);
        free(w -> herois[i]);
    }
    free(w -> herois);

    //liberando bases
    for(int i = 0; i < w -> n_bases; i++){

        cjto_destroi(w -> bases[i] -> equipe);
        fila_destroi(w -> bases[i] -> f_espera);
        free(w -> bases[i] -> local_base);
        free(w -> bases[i]);
    }
    free(w -> bases);

    //liberando missoes
    for(int i = 0; i < w -> n_missoes; i++){

        cjto_destroi(w -> missoes[i] -> hab_necessarias);
        free(w -> missoes[i] -> local_missao);
        free(w -> missoes[i]);
    }
    free(w -> missoes);

    //liberando invasoes
    for(int i = 0; i < w -> n_invasoes; i++){
        free(w -> invasoes[i]);
    }
    free(w -> invasoes);

    free(w -> tam_mundo);
    fprio_destroi(w -> lef);
    free(w);
    return NULL;
}
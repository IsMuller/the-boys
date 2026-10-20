#include <stdio.h>
#include <stdlib.h>
#include "funcoes_extras.h"
#include "entidades.h"
#include "inicializa.h"
#include "conjuntos.h"
#include "fila.h"


void inicializa_heroi(struct heroi *h, int id) {//inicializa um heroi a partir de seu id 
    int quant_habilidades;
    h -> id = id;
    h -> experiencia = 0;
    h -> paciencia = aleat(0, 100);
    h -> velocidade = aleat(50, 5000);
    quant_habilidades = aleat(1, 3);
    h -> habilidades = cjto_aleat(quant_habilidades, N_HABILIDADES); //cria um conjunto de n habilidades aleatorias
}

void inicializa_base(struct base *b, int id) {//inicializa uma base a partir de seu id
    b -> id = id;
    b ->local_base = malloc(sizeof(struct localizacao));
    b -> local_base -> x = aleat(0, N_TAMANHO_MUNDO - 1);
    b -> local_base -> y = aleat(0, N_TAMANHO_MUNDO - 1);
    b -> max = aleat(3, 10);
    b -> equipe = cjto_cria(b -> max);
    b -> f_espera = fila_cria();
}

void inicializa_missao(struct missao *m, int id) {//inicializa uma missao a partir de seu id
    int quant_habilidades;
    m -> id = id;
    m -> local_missao = malloc(sizeof(struct localizacao));
    m -> local_missao -> x = aleat(0, N_TAMANHO_MUNDO - 1);
    m-> local_missao -> y = aleat(0, N_TAMANHO_MUNDO - 1);
    quant_habilidades = aleat(6, 10);
    m -> habilidades = cjto_aleat(quant_habilidades, N_HABILIDADES);
    m -> perigo = aleat(0, 100);
}

void inicializa_invasao(struct invasao *i, int id) {//inicializa uma invasao a partir de seu id
    i -> id = id;
    i -> id_base = aleat(0, N_BASES - 1);
    i -> t_penalidade_heroi= aleat(0, 4320);
    i -> t_penalidade_base = aleat(0, 7200);
}

struct mundo *inicializa_mundo();//inicializa o mundo, utilizando todas as funcoes anteriores
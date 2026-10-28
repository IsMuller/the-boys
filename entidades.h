//arquivo que descreve as entidades(caracteristicas) do projeto
#ifndef ENTIDADES
#define ENTIDADES
#include "fila.h"
#include "fprio.h"
#include "conjunto.h"

struct heroi {
    int id; //identifica o heroi
    int morto; //identifica se heroi esta morto (1) ou vivo (0)
    int estado; //indica se esta ativo (1) ou inativo(0)
    struct cjto_t *habilidades; //conjunto das habilidades do heroi
    int paciencia; //nivel de paciencia do heroi
    int velocidade; //velocidade do heroi
    int experiencia; //indica o numero de missoes que o heroi teve
    int base; //id da base que o heroi esta
};

struct localizacao { //descreve o par de coordenada da localizacao desejada
    int x;
    int y;
};

struct base {
    int id; //identifica a base
    int max; //num maximo de herois que podem estar na base
    int f_max; //num maximo de herois na fila de espera da base
    int missoes; //quant de missoes da base
    struct cjto_t *equipe; //conjunto dos ids do herois presentes
    int estado; //indica se esta ativa (1) ou inativa (0);
    struct fila_t *f_espera; //fila de espera da base
    struct localizacao *local_base; //coordenadas da base
};

struct missao{
    int id; //identifica a missao
    struct cjto_t *hab_necessarias; //conjunto com as habilidades necessarias p/ a missao
    int tentativas; //quant de tentativas da missao
    int perigo; //nivel de perigo da missao
    struct localizacao *local_missao; //coordenadas da missao
};

struct invasao {
    int id; // identifica a invasao
    int id_base; // id base onde sera realizada a invasao
    int t_penalidade_base; // Tempo em que a base permanece inativa
    int t_penalidade_heroi; // Tempo em que os herois permanecem inativos
};

struct mundo {
    int n_herois; //numero de herois total
    struct heroi **herois; //vetor de ponteiros que apontam para cada struct heroi

    int n_bases; //numero de bases total
    struct base **bases; //vetor de ponteiros que apontam para cada struct base

    int n_missoes; //numero total de missoes a se cumprir
    int n_missoes_cumpridas; //numero total de missoes cumpridas
    struct missao **missoes; //vetor de ponteiros que apontam para cada struct missao

    int n_invasoes; //numero total de invasoes marcadas
    int n_invasoes_realizadas; // numero de invasoes feitas
    struct invasao **invasoes; //vetor de ponteiros que apontam para cada struct invasao

    int n_habilidades; //numero total de habilidades distintas no mundo

    int n_eventos_tratados; //quant de eventos tratados;
    
    struct localizacao *tam_mundo; //coordenadas do x max e y max do mundo

    int min_atual; //tempo atual do mundo

    struct fprio_t *lef; //lista de eventos futuros do mundo
};

#endif

// programa principal do projeto "The Boys - 2026/2"
// Autor: ISADORA MÜLLER, GRR 20263994
#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "inicializa.h"
#include "simulacao.h"

//programa principal
int main() {
    //inicializando o mundo
    struct mundo *w = inicializa_mundo();
    if (!w) {
        return 1;
    }
    // criando eventos iniciais e os inserindo na LEF
    eventos_iniciais(w);
    //simulando o mundo;
    simula_mundo(w);
    //destruindo o mundo
    w = destroi_mundo(w);
    return 0;
}



#include <stdlib.h>
#include <math.h> //para termos acesso a srqt e pow
#include "funcoes_extras.h"

int aleat(int min, int max){
    return min + rand() % (max - min + 1); 
}

double distancia_cartesiana(struct localizacao *l1, struct localizacao *l2){
    return sqrt(pow(l2 -> x - l1 -> x, 2) + pow(l2 -> y - l1 -> y, 2));
}


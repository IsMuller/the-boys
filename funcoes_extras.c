#include <stdlib.h>
#include "funcoes_extras.h"


int aleat(int min, int max){
    return min + rand() % (max - min + 1); 
}
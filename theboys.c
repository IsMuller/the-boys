// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
//int main ()
//{
  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo
 // return (0) ;
//}
#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "inicializa.h"
#include "eventos.h"
#include "fila.h"
#include "fprio.h" // Ou o cabeçalho da sua LEF
#include <string.h>


int main() {
    printf("=== INICIANDO TESTE DA SIMULACAO ===\n");

    // 1. Inicializa o mundo
    struct mundo *w = inicializa_mundo();
    if (!w) {
        printf("ERRO: Falha ao alocar o mundo!\n");
        return 1;
    }
    printf("[SUCESSO] Mundo inicializado!\n");
    printf(" - Heróis criados: %d\n", w->n_herois);
    printf(" - Bases criadas: %d\n", w->n_bases);
    printf(" - Missões criadas: %d\n", w->n_missoes);
    printf(" - Invasões criadas: %d\n", w->n_invasoes);

    // 2. Cria e injeta os eventos iniciais na LEF
    eventos_iniciais(w);
    printf("[SUCESSO] Eventos iniciais injetados na LEF!\n");

    // 3. Teste rápido retirando alguns eventos da LEF para ver se estão lá
    printf("\n--- TESTANDO RETIRADA DE EVENTOS DA LEF ---\n");
    for (int i = 0; i < 5; i++) {
        int tipo;
        int tempo;
        struct evento *ev = fprio_retira(w->lef, &tipo, &tempo);
        
        if (ev) {
            printf("Evento %d -> Tipo: %d | Tempo: %d\n", i + 1, ev->tipo, ev->tempo);
            // Liberando o evento de teste
            free(ev);
        } else {
            printf("LEF vazia ou sem mais eventos.\n");
            break;
        }
    }

    printf("\n=== TESTE FINALIZADO COM SUCESSO! ===\n");
    return 0;
}



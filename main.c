#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // Essencial para o rand()

#include "estruturas.h"

// Função auxiliar para imprimir os pacientes nos leitos
void imprimir_leitos(ListaLeitos* ll) {
    printf("--- Estado dos Leitos (Ocupação: %d/%d) ---\n", ll->ocupacao, CAPACIDADE_LEITOS);
    for (int i = 0; i < ll->ocupacao; i++) {
        printf("Leito %d: [ID: %s, Nome: %s]\n", i + 1, ll->pacientes[i].id, ll->pacientes[i].nomeCompleto);
    }
    if (leitos_esta_vazio(ll)) {
        printf("Todos os leitos estão vazios.\n");
    }
    printf("--------------------------------------------\n");
}

int main() {
    // Inicializa o gerador de números aleatórios. FAÇA ISSO APENAS UMA VEZ!
    srand(time(NULL));

    printf("--- Testando Módulo de Lista de Leitos ---\n");
    ListaLeitos* leitos = leitos_criar();

    // Adiciona alguns pacientes
    leitos_adicionar(leitos, (Paciente){"PAC001", "Carlos Silva"});
    leitos_adicionar(leitos, (Paciente){"PAC002", "Maria Souza"});
    leitos_adicionar(leitos, (Paciente){"PAC007", "Ana Costa"});
    leitos_adicionar(leitos, (Paciente){"PAC015", "Jose Lima"});

    imprimir_leitos(leitos);

    // Dando alta para um paciente aleatório
    printf("\nDando alta para um paciente aleatório...\n");
    Paciente paciente_de_alta = leitos_remover_aleatorio(leitos);
    printf("ALTA: Paciente %s (ID: %s) recebeu alta.\n\n", paciente_de_alta.nomeCompleto, paciente_de_alta.id);

    imprimir_leitos(leitos);

    return 0;
}
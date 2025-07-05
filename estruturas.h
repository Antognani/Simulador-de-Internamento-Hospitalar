// estruturas.h
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "paciente.h" // Precisa saber o que é um Paciente

// Definições das estruturas (Node, Pilha, Deque, TabelaHash, etc.)
typedef struct No {
    Paciente paciente;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct {
    No* cabeca;
    No* fim;
} Lista;

typedef struct {
    No* frente;
    No* tras;
} Deque;

typedef struct {
    No* topo;
} Pilha;

typedef struct {
    int tamanho;
    Lista* tabela;
} TabelaHash;


// Protótipos das funções do Deque
Deque* deque_criar();
void deque_inserir_frente(Deque* d, Paciente p);
void deque_inserir_fim(Deque* d, Paciente p);
// ... outros protótipos

// Protótipos das funções da Pilha
Pilha* pilha_criar();
void pilha_push(Pilha* p, Paciente pac);
// ... outros protótipos

// ... protótipos para Tabela Hash e Lista de Leitos

#endif // ESTRUTURAS_H
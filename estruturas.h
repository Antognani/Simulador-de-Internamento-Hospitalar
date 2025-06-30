// estruturas.h
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "paciente.h" // Precisa saber o que é um Paciente

// Definições das estruturas (Node, Pilha, Deque, TabelaHash, etc.)
typedef struct Node {
    Paciente paciente;
    struct Node* proximo;
    struct Node* anterior;
} Node;

typedef struct Deque { /* ... */ } Deque;
typedef struct Pilha { /* ... */ } Pilha;
// ... e assim por diante

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
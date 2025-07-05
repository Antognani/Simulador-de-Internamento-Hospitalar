// estruturas.h
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "paciente.h" 
#define CAPACIDADE_LEITOS 10


typedef struct No {
    Paciente paciente;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct ListaLeitos {
    Paciente pacientes[CAPACIDADE_LEITOS]; //qntd leitos
    int ocupacao; //qntd pacientes internados
} ListaLeitos;

typedef struct Deque {
    No* frente;
    No* tras;
    int tamanho;
    int capacidade; //max 20
} Deque;

typedef struct Pilha {
    No* topo;
} Pilha;

typedef struct TabelaHash {
    No** tabela; //array de ponteiros para No
    int tamanho; //tamanho da tabela hash
} TabelaHash;


//PILHA
Pilha* pilhaIniciar(Pilha* p);
void pilhaPush(Pilha* p, Paciente pac);
int pilhaEstaVazia(Pilha* p);
Paciente pilhaPop(Pilha* p);
void exibirPilha(Pilha* p);

//DEQUE
Deque* dequeIniciar(int capacidade);
int dequeEstaCheio(Deque* d);
int dequeEstaVazio(Deque* d);
void dequeInserirInicio(Deque* d, Paciente pac);
void dequeInserirFim(Deque* d, Paciente pac);
Paciente dequeRemoverCabeca(Deque* d);
Paciente dequeRemoverFim(Deque* d);
Paciente dequeRemoverPorPrioridade(Deque* d);

//TABELA HASH
TabelaHash* tabelaHashIniciar(int tamanho);
void tabelaHashInserir(TabelaHash* th, Paciente pac);
Paciente* tabelaHashProcurar(TabelaHash* th, const char* id);
void tabelaHashImprimir(TabelaHash* th)

//LISTA DE LEITOS
ListaLeitos* LeitosIniciar();
void LeitosAdicionar(ListaLeitos* ll, Paciente paciente);
int leitosEstaCheio(ListaLeitos* ll);
int leitosEstaVazio(ListaLeitos* ll);
Paciente leitosRemoverAleatorio(ListaLeitos* ll);

#endif
// estruturas.h
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "paciente.h" 
#define CAPACIDADE_LEITOS 10

//ESTRUTURAS DE DADOS

//NÓ
typedef struct No {
    Paciente paciente;
    struct No* proximo;
    struct No* anterior;
} No;

//LISTA DE LEITOS
typedef struct ListaLeitos {
    Paciente pacientes[CAPACIDADE_LEITOS]; //qntd leitos
    int ocupacao; //qntd pacientes internados
} ListaLeitos;

//DEQUE
typedef struct Deque {
    No* frente;
    No* tras;
    int tamanho;
    int capacidade; //max 20
} Deque;

//PILHA
typedef struct Pilha {
    No* topo;
} Pilha;

//TABELA HASH
typedef struct TabelaHash {
    No** tabela; //array de ponteiros para No
    int tamanho; //tamanho da tabela hash
} TabelaHash;


//FUNÇÕES DA PILHA
Pilha* pilhaIniciar();
void pilhaPush(Pilha* p, Paciente pac);
int pilhaEstaVazia(Pilha* p);
Paciente pilhaPop(Pilha* p);
void exibirPilha(Pilha* p);

//FUNÇÕES DO DEQUE
Deque* dequeIniciar(int capacidade);
int dequeEstaCheio(Deque* d);
int dequeEstaVazio(Deque* d);
void dequeInserirCabeca(Deque* d, Paciente pac);
void dequeInserirFim(Deque* d, Paciente pac);
Paciente dequeRemoverCabeca(Deque* d);
Paciente dequeRemoverFim(Deque* d);
Paciente dequeRemoverPorPrioridade(Deque* d);

//FUNÇÕES DA TABELA HASH
TabelaHash* tabelaHashIniciar(int tamanho);
void tabelaHashInserir(TabelaHash* th, Paciente pac);
Paciente* tabelaHashProcurar(TabelaHash* th, const char* id);
void tabelaHashImprimir(TabelaHash* th);
Paciente* tabelaHashSorteioPacNaoAtendido(TabelaHash* th);

//FUNÇÕES DA LISTA DE LEITOS
ListaLeitos* LeitosIniciar();
void LeitosAdicionar(ListaLeitos* ll, Paciente paciente);
int leitosTemPacienteAptoAlta(ListaLeitos* ll);
void leitosIncrementarCiclos(ListaLeitos* ll);
int leitosEstaCheio(ListaLeitos* ll);
int leitosEstaVazio(ListaLeitos* ll);
Paciente leitosRemoverAleatorio(ListaLeitos* ll);

//DESTRUTORES
void pilhaDestruir(Pilha* p);
void dequeDestruir(Deque* d);
void tabelaHashDestruir(TabelaHash* th);
void leitosDestruir(ListaLeitos* ll);
#endif
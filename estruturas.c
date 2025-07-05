// estruturas.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

//IMPLEMENTAÇÃO DAS PILHAS
//INICIALIZAÇÃO PILHA
Pilha* pilhaIniciar() {
   Pilha* novaPilha = (Pilha*) malloc(sizeof(Pilha));
    if (novaPilha != NULL) {
        novaPilha->topo = NULL;
    }
    return novaPilha;
}

//REMOÇÃO PILHA
void pilhaPush(Pilha* p, Paciente pac) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac;
    novoNo->proximo = p->topo; //novo nó aponta para o topo atual
    p->topo = novoNo; //novo nó vira o topo
}
 
//EXIBIÇÃO PILHA
Paciente pilhaPop(Pilha* p) {
    if (pilhaEstaVazia(p)) {
        fprintf(stderr, "Pilha vazia. Não é possível remover elementos.\n");
        exit(EXIT_FAILURE);
    }
    No* noRemovido = p->topo;
    Paciente pacientePopado = noRemovido->paciente;
    p->topo = noRemovido->proximo;
    free(noRemovido);
    return pacientePopado;
}

//AUX
int pilhaEstaVazia(Pilha* p) {
    return p->topo == NULL;
}

//IMPLEMENTAÇÃO DO DEQUE
Deque* dequeIniciar(int capacidade){
    Deque* novoDeque = (Deque*)malloc(sizeof(Deque));
    if (novoDeque != NULL) {
        novoDeque->frente = NULL;
        novoDeque->tras = NULL;
        novoDeque->tamanho = 0;
        novoDeque->capacidade = capacidade; //20 (não esquecer de setar isso)
    }
    return novoDeque;
}

//AUX
int dequeEstaCheio(Deque* d) {
    return d->tamanho >= d->capacidade;
}

//AUX
int dequeEstaVazio(Deque* d) {
    return d->tamanho == 0;
}

//INSERÇÃO HEAD
void dequeInserirCabeca(Deque* d, Paciente pac) {
    if (dequeEstaCheio(d)) {
        fprintf(stderr, "Deque cheio. Não é possível inserir elementos.\n");
        return;
    }
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) { 
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac;
    novoNo->anterior = NULL;
    novoNo->proximo = d->frente;

    if (dequeEstaVazio(d)) {
        d->frente = d;
    } else {
        d->frente->anterior = novoNo;
        d->frente = novoNo;
    }
    d->tamanho++;
}

//INSERÇÃO FIM
void dequeInserirFim(Deque* d, Paciente pac) {
    if (dequeEstaCheio(d)) {
        fprintf(stderr, "Deque cheio. Não é possível inserir elementos.\n");
        return;
    }
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac;
    novoNo->proximo = NULL;
    novoNo->anterior = d->tras;

    if (dequeEstaVazio(d)) {
        d->frente = d->tras = novoNo;
    } else {
        d->tras->proximo = novoNo;
        d->tras = novoNo;
    }
    d->tamanho++;
}

//REMOÇÃO HEAD
Paciente dequeRemoverCabeca(Deque* d) {
    if (dequeEstaVazio(d)) {
        fprintf(stderr, "Deque vazio. Não é possível remover elementos.\n");
        exit(EXIT_FAILURE);
    }
    No* noRemovido = d->frente;
    Paciente pacienteRemovido = noRemovido->paciente;

    d->frente = noRemovido->proximo;
    if (d->frente != NULL) {
        d->frente->anterior = NULL;
    } else {
        d->tras = NULL; // Se o deque ficar vazio
    }
    free(noRemovido);
    d->tamanho--;
    return pacienteRemovido;
}

//REMOÇÃO FIM
Paciente dequeRemoverFim(Deque* d) {
    if (dequeEstaVazio(d)) {
        fprintf(stderr, "Deque vazio. Não é possível remover elementos.\n");
        exit(EXIT_FAILURE);
    }
    No* noRemovido = d->tras;
    Paciente pacienteRemovido = noRemovido->paciente;

    d->tras = noRemovido->anterior;
    if (d->tras != NULL) {
        d->tras->proximo = NULL;
    } else {
        d->frente = NULL; // Se o deque ficar vazio
    }
    free(noRemovido);
    d->tamanho--;
    return pacienteRemovido;
}

//REMOÇÃO POR PRIORIDADE
Paciente dequeRemoverPorPrioridade(Deque* d) {
    if (dequeEstaVazio(d)) {
        fprintf(stderr, "Deque vazio. Não é possível remover elementos.\n");
        exit(EXIT_FAILURE);
    }

    if (d->tamanho == 1) { //se so tiver 1 pac, remove ele
        return dequeRemoverCabeca(d);
    }

    Paciente p_frente = d->frente->paciente; //paciente da cabeca
    Paciente p_tras = d->tras->paciente; //paciente do fim

    //remove o paciente que tem a maior prioridade entre os extremos
    //caos impate, prioriza o da cabeca
    if (p_frente.prioridade >= p_tras.prioridade) { 
        return dequeRemoverCabeca(d); //remove o paciente da frente
    } else {
        return dequeRemoverFim(d); //remove o paciente do fim
    }

}

//IMPLEMENTAÇÃO HASH TABLE
//FUNÇÃO HASH (usada DJB2 pela confiabilidade e simplicidade)
//ref: https://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char* id, int tamanho) {
    unsigned long hash = 5381;
    int c;
    while ((c = *id++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % tamanho;
}

//inicializa a tabela hash
TabelaHash* tabelaHashIniciar(int tamanho) {
    TabelaHash* novaTabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (novaTabela != NULL) {
        novaTabela->tamanho = tamanho;
        novaTabela->tabela = (No**)malloc(tamanho * sizeof(No*));
        if (novaTabela->tabela == NULL) {
            fprintf(stderr, "Erro ao alocar memória para a tabela hash.\n");
            free(novaTabela);
            return NULL;
        }
        for (int i = 0; i < tamanho; i++) {
            novaTabela->tabela[i] = NULL; //inicializa todos os ponteiros
        }
    }
    return novaTabela;
}

//INSERÇÃO TABELA HASH
void tabelaHashInserir(TabelaHash* th, Paciente pac) {
    //calcula o index usando funcao hash
    unsigned int indice = hash(pac.id, th->tamanho);

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac;
    novoNo->proximo = th->tabela[indice];
    th->tabela[indice] = novoNo;
}

//BUSCA NA TABELA HASH (procura um pac pelo ID e retorna um ponteiro pra ele)
Paciente* tabelaHashProcurar(TabelaHash* th, const char* id) {
    unsigned int indice = hash(id, th->tamanho);
    No* atual = th->tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->paciente.id, id) == 0) { //se strings iguais, retorna 0
            return &atual->paciente; //retorna o ponteiro para o paciente encontrado
        }
        atual = atual->proximo; //avança para o próximo nó
    }
    return NULL; //não encontrou
}

//AUX PRINTAR CONTEUDO
void tabelaHashPrintar(TabelaHash* th) {
    printf("----------Tabela Hash:----------\n");
    for (int i = 0; i < th->tamanho; i++) {
        printf("Indice %d: ", i);
        No* atual = th->tabela[i];
        if (atual == NULL) {
            printf("Vazio\n");
        } else {
            while (atual != NULL) {
                printf("ID: %s, Nome: %s] -> ", atual->paciente.id, atual->paciente.nomeCompleto);
                atual = atual->proximo;
            }
            printf("NULL\n");
        }
    }
    printf("-------------------------------\n");
}

ListaLeitos* LeitosIniciar() {
    ListaLeitos* ll= (ListaLeitos*)malloc(sizeof(ListaLeitos));
    if (ll!= NULL) {
        ll->ocupacao = 0; //inicializa ocupacao
    }
    return ll;
}

int leitosEstaCheio(ListaLeitos* ll) {
    return ll->ocupacao >= CAPACIDADE_LEITOS; //verifica se a ocupacao é maior ou igual a capacidade
}

int leitosEstaVazio(ListaLeitos* ll) {
    return ll->ocupacao == 0; //verifica se a ocupacao é igual a 0
}

void LeitosAdicionar(ListaLeitos* ll, Paciente paciente) {
    if (leitosEstaCheio(ll)) {
        fprintf(stderr, "Lista de leitos cheia. Não é possível adicionar pacientes.\n");
        return;
    }
    ll->pacientes[ll->ocupacao] = paciente; //adiciona o paciente na lista
    ll->ocupacao++; //incrementa a ocupacao
}

Paciente leitosRemoverAleatorio(ListaLeitos* ll) {
    if (leitosEstaVazio(ll)) {
        fprintf(stderr, "Lista de leitos vazia. Não é possível remover pacientes.\n");
        exit(EXIT_FAILURE);
    }

    // Gera um índice aleatório
    int indice = rand() % ll->ocupacao;

    // Salva o paciente a ser removido
    Paciente pacienteRemovido = ll->pacientes[indice];

    // Move o último paciente para o lugar do removido
    ll->pacientes[indice] = ll->pacientes[ll->ocupacao - 1];
    ll->ocupacao--; // Decrementa a ocupação

    return pacienteRemovido;
}
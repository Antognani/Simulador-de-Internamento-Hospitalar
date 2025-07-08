// estruturas.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

//IMPLEMENTAÇÃO DAS PILHAS
//INICIALIZAÇÃO PILHA
Pilha* pilhaIniciar() {
   Pilha* novaPilha = (Pilha*) malloc(sizeof(Pilha)); //aloca memória para a nova pilha
    if (novaPilha) {
        novaPilha->topo = NULL; //inicializa o topo como NULL
    }
    return novaPilha;
}

//REMOÇÃO PILHA
void pilhaPush(Pilha* p, Paciente pac) {
    No* novoNo = (No*)malloc(sizeof(No)); //aloca memória para o novo nó
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac; //armazena o paciente no novo nó
    novoNo->proximo = p->topo; //novo nó aponta para o topo atual
    p->topo = novoNo; //novo nó vira o topo
}

//AUX
int pilhaEstaVazia(Pilha* p) {
    return p->topo == NULL;
}

//IMPLEMENTAÇÃO DO DEQUE
Deque* dequeIniciar(int capacidade){
    Deque* novoDeque = (Deque*)malloc(sizeof(Deque)); //aloca memória para o novo deque
    if (novoDeque) {
        novoDeque->frente = NULL; //inicializa a frente como NULL
        novoDeque->tras = NULL; //inicializa a tras como NULL
        novoDeque->tamanho = 0; //inicializa o tamanho como 0
        novoDeque->capacidade = capacidade; //20 (não esquecer de setar isso)
    }
    return novoDeque;
}

//AUX
int dequeEstaCheio(Deque* d) {
    return d->tamanho >= d->capacidade; //verifica se o deque está cheio
}

//AUX
int dequeEstaVazio(Deque* d) {
    return d->tamanho == 0; //verifica se o deque está vazio
}

//INSERÇÃO HEAD
void dequeInserirCabeca(Deque* d, Paciente pac) {
    No* novoNo = (No*)malloc(sizeof(No)); //aloca memória pro novo nó
    if (novoNo == NULL) { 
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac; //armazena o paciente no novo nó
    novoNo->anterior = NULL; //novo nó não tem nó anterior
    novoNo->proximo = d->frente; //novo nó aponta pra cabeça atual

    if (dequeEstaVazio(d)) {
        d->frente = d->tras = novoNo;  //se estiver vazio, novo nó é a cabeça e o no final
    } else {
        d->frente->anterior = novoNo; //novo nó se torna o novo nó anterior da cabeça
        d->frente = novoNo; //atualiza a cabeça para o novo nó
    }
    d->tamanho++; //incrementa o tamanho do deque
}

//INSERÇÃO FIM
void dequeInserirFim(Deque* d, Paciente pac) {
    No* novoNo = (No*)malloc(sizeof(No)); //aloca memória para o novo nó
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac; //armazena o paciente no novo nó
    novoNo->proximo = NULL; // novo nó não tem nó seguinte
    novoNo->anterior = d->tras; //novo nó aponta para o atual último nó

    if (dequeEstaVazio(d)) { //se o deque estiver vazio, o novo nó é tanto a cabeça quanto o fim
        d->frente = d->tras = novoNo; //se estiver vazio, novo nó é a cabeça e a fim
    } else {
        d->tras->proximo = novoNo; //atualiza o próximo do último nó
        novoNo->anterior = d->tras; //atualiza o novo nó
    }
    d->tamanho++; //incrementa o tamanho do deque
}

//REMOÇÃO HEAD
Paciente dequeRemoverCabeca(Deque* d) {
    No* noRemovido = d->frente; //pega o nó da frente
    Paciente pacienteRemovido = noRemovido->paciente; //armazena o paciente removido

    d->frente = noRemovido->proximo; //atualiza a frente para o próximo nó
    if (d->frente) { //se a frente não for NULL
        d->frente->anterior = NULL; //atualiza o anterior da nova frente
    } else {
        d->tras = NULL; //se o deque ficar vazio, atualiza a tras para NULL
    }
    free(noRemovido); //libera a memória do nó removido
    d->tamanho--; //decrementa o tamanho do deque
    return pacienteRemovido; //retorna o paciente removido
}

//REMOÇÃO FIM
Paciente dequeRemoverFim(Deque* d) {
    No* noRemovido = d->tras; //pega o nó da tras
    Paciente pacienteRemovido = noRemovido->paciente; //armazena o paciente removido

    d->tras = noRemovido->anterior; //atualiza a tras para o nó anterior
    if (d->tras) { //se a tras não for NULL
        d->tras->proximo = NULL; //atualiza o próximo da nova tras
    } else {
        d->frente = NULL; //se o deque ficar vazio, atualiza a frente para NULL
    }
    free(noRemovido); //libera a memória do nó removido
    d->tamanho--; //decrementa o tamanho do deque
    return pacienteRemovido; //retorna o paciente removido
}

//REMOÇÃO POR PRIORIDADE
Paciente dequeRemoverPorPrioridade(Deque* d) {
    if (d->tamanho == 1) { //se so tiver 1 pac, remove ele
        return dequeRemoverCabeca(d); //remove o único paciente
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
//FUNÇÃO HASH (usada DJB2 pq tem mais confiabilidade e simplicidade)
//ref: https://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char* id, int tamanho) {
    unsigned long hash = 5381; // inicializa o hash com um valor primo quase perfeito (definido na doc do djb2)
    int c; 
    while ((c = *id++)) { // enquanto houver caracteres na string
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % tamanho; // retorna o índice na tabela hash
}

//inicializa a tabela hash
TabelaHash* tabelaHashIniciar(int tamanho) {
    TabelaHash* novaTabela = (TabelaHash*)malloc(sizeof(TabelaHash)); //aloca memória para a nova tabela hash
    if (novaTabela) {
        novaTabela->tamanho = tamanho; //define o tamanho da tabela hash
        novaTabela->tabela = (No**)malloc(tamanho * sizeof(No*)); // aloca memória para o array de ponteiros
        if (novaTabela->tabela == NULL) {
            fprintf(stderr, "Erro ao alocar memória para a tabela hash.\n");
            free(novaTabela);
            return NULL;
        }
        for (int i = 0; i < tamanho; i++) {
            novaTabela->tabela[i] = NULL; //inicializa todos os ponteiros
        }
    }
    return novaTabela; //retorna a nova tabela hash
}

//INSERÇÃO TABELA HASH
void tabelaHashInserir(TabelaHash* th, Paciente pac) {
    //calcula o index usando funcao hash
    unsigned int indice = hash(pac.id, th->tamanho); //calcula o índice na tabela hash

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->paciente = pac; //armazena o paciente no novo nó
    novoNo->proximo = th->tabela[indice]; //novo nó aponta para o nó atual na tabela
    th->tabela[indice] = novoNo; //insere o novo nó no início da lista encadeada
}

//INICIALIZA LISTA DOS LEITOS
ListaLeitos* LeitosIniciar() {
    ListaLeitos* ll= (ListaLeitos*)malloc(sizeof(ListaLeitos));
    if (ll) {  //verifica se a alocação deu certo
        ll->ocupacao = 0; //inicializa ocupacao
    }
    return ll; //retorna a lista de leitos inicializada
}

//INCREMENTA CICLOS INTERNADO
void leitosIncrementarCiclos(ListaLeitos* ll) {
    for (int i = 0; i < ll->ocupacao; i++) { //itera por todos os pacientes
        ll->pacientes[i].ciclosInternado++; //incrementa o ciclo de internamento de cada paciente
    }
}

//AUX CHECA SE HÁ PACIENTES APTOS PARA ALTA
//inserido pois estava ocorrendo Segmentation Fault devido alta de pacientes não aptos
int leitosTemPacienteAptoAlta(ListaLeitos* ll) { 
    for (int i = 0; i < ll->ocupacao; i++) { //itera por todos os pacientes
        if (ll->pacientes[i].ciclosInternado >= 1) { //verifica se o paciente está apto para alta
            return 1; //se sim, retorna 1
        }
    }
    return 0; //se não, retorna 0
}

//AUX CHECA SE LEITOS ESTAO CHEIOS
int leitosEstaCheio(ListaLeitos* ll) {
    return ll->ocupacao >= CAPACIDADE_LEITOS; //verifica se a ocupacao é maior ou igual a capacidade
}

//AUX CHECA SE OS LEITOS ESTAO VAZIOS
int leitosEstaVazio(ListaLeitos* ll) {
    return ll->ocupacao == 0; //verifica se a ocupacao é igual a 0
}

//MOVE PACIENTE A UM LEITO
void LeitosAdicionar(ListaLeitos* ll, Paciente paciente) {
    if (leitosEstaCheio(ll)) { //verifica se a lista de leitos está cheia
        //se estiver cheia, exibe mensagem de erro e encerra o programa (tratamento de exceção)
        fprintf(stderr, "Lista de leitos cheia. Não é possível adicionar pacientes.\n");
        return;
    }
    ll->pacientes[ll->ocupacao] = paciente; //adiciona o paciente na lista
    ll->ocupacao++; //incrementa a ocupacao
}

// REMOVE PAC ALEAT. (escolhe aleatoriamente (usando rand()) um paciente para dar alta)
Paciente leitosRemoverAleatorio(ListaLeitos* ll) { 
    if (leitosEstaVazio(ll)) { //verifica se a lista de leitos está vazia
        //se estiver vazia, exibe mensagem de erro e encerra o programa (tratamento de exceção)
        fprintf(stderr, "Lista de leitos vazia. Não é possível remover pacientes.\n");
        exit(EXIT_FAILURE);
    }

    int indice = rand() % ll->ocupacao; //gera um número aleatório entre 0 e (ocupacao - 1)

    Paciente pacienteRemovido = ll->pacientes[indice]; //salva o paciente a ser removido

    //move o último paciente para o lugar do removido
    ll->pacientes[indice] = ll->pacientes[ll->ocupacao - 1]; //substitui o paciente removido pelo último
    ll->ocupacao--; //decrementa a ocupacao

    return pacienteRemovido; //retorna o paciente removido
}

// REMOVE PACIENTE ALEATÓRIO APTO PARA ALTA
Paciente leitosRemoverAleatorioApto(ListaLeitos* ll) {
    int aptos = 0; //contador de pacientes aptos para alta
    for (int i = 0; i < ll->ocupacao; i++) { //itera por todos os pacientes
        if (ll->pacientes[i].ciclosInternado >= 1) { //verifica se o paciente ta apto pra alta
            aptos++; //incrementa o contador de pacientes aptos
        }
    }
    //se não tiver paciente apto pra alta, exibe mensagem de erro e encerra o programa (tratamento de exceção)
    if (aptos == 0) {
        fprintf(stderr, "Nenhum paciente apto para alta.\n");
        exit(EXIT_FAILURE); 
    }
    int* indices = (int*)malloc(aptos * sizeof(int)); //aloca memória para os índices dos pacientes aptos
    int idx = 0; //inicializa o índice dos pacientes aptos
    for (int i = 0; i < ll->ocupacao; i++) { //itera por todos os pacientes
        if (ll->pacientes[i].ciclosInternado >= 1) { //verifica se o paciente ta apto pra alta
            indices[idx++] = i; //armazena os índices dos pacientes aptos
        }
    }
    int sorteado = indices[rand() % aptos]; //gera um número aleatório entre 0 e (aptos - 1)
    Paciente pacienteRemovido = ll->pacientes[sorteado]; //salva o paciente a ser removido
    ll->pacientes[sorteado] = ll->pacientes[ll->ocupacao - 1]; //substitui o paciente removido pelo último
    ll->ocupacao--; //decrementa a ocupação
    free(indices); //libera a memória alocada para os índices
    return pacienteRemovido; //retorna o paciente removido
}

//SORTEIA PACIENTE NÃO ATENDIDO DA TABELA HASH PRA FILA DE ESPERA
Paciente* tabelaHashSorteioPacNaoAtendido(TabelaHash* th){

    int contador = 0; 
    //verifica quantos pacientes não atendidos existem na tabela hash  
    for (int i = 0; i < th->tamanho; i++) { 
        No* atual = th->tabela[i]; //pega o nó atual
        while (atual) {
            if (atual->paciente.atendido == 0) { //se paciente não foi atendido
                contador++; //incrementa o contador
            } 
            atual = atual->proximo; //avança para o próximo nó
        }
    }
    if (contador == 0) {
        fprintf(stderr, "Nenhum paciente não atendido encontrado.\n");
        return NULL; //não há pacientes não atendidos
}
    //checar quais são os pacientes aptos
    Paciente** lista_aptos = (Paciente**)malloc(contador * sizeof(Paciente*));
    int indice_lista = 0; //inicializa o índice da lista de pacientes aptos
    //preenche a lista de pacientes aptos
    for (int i = 0; i < th->tamanho; i++) { //itera por cada índice da tabela
        No* atual = th->tabela[i]; //pega o nó atual
        while (atual) {
            if (atual->paciente.atendido == 0) { //se paciente não foi atendido
                lista_aptos[indice_lista] = &atual->paciente; //adiciona o ponteiro do paciente na lista
                indice_lista++; //incrementa o índice da lista de aptos
            }
            atual = atual->proximo; //avança para o próximo nó
        }
    }

    //sorteia um paciente da lista de aptos
    int sorteio = rand() % contador; //gera um número aleatório entre 0 e contador - 1
    Paciente* pacienteSorteado = lista_aptos[sorteio]; //pega o ponteiro para o paciente sorteado
    free(lista_aptos); //libera a memória alocada para a lista de aptos
    return pacienteSorteado; //retorna o ponteiro para o paciente sorteado
}

//DESTRUTORES
void pilhaDestruir(Pilha* p) {
    No* atual = p->topo; //pega o nó do topo
    while (atual) {
        No* proximo = atual->proximo; //salva o próximo nó
        free(atual); //libera o nó atual
        atual = proximo; //avança para o próximo nó
    }
    free(p); //libera a pilha
}

void dequeDestruir(Deque* d) {
    No* atual = d->frente; //começa do nó da frente
    //itera por todos os nós do deque e libera a memória alocada
    while (atual) {
        No* proximo = atual->proximo; //salva o próximo nó
        free(atual); //libera o nó atual
        atual = proximo; //avança para o próximo nó
    }
    free(d); //libera o deque
}

//destrói a tabela hash e libera a memória alocada
void tabelaHashDestruir(TabelaHash* th) {
    for (int i = 0; i < th->tamanho; i++) { //itera por cada índice da tabela
        No* atual = th->tabela[i]; //pega o nó atual
        while (atual) { 
            No* proximo = atual->proximo; //salva o próximo nó
            free(atual); //libera o nó atual
            atual = proximo; //avança para o próximo nó
        } 
    }
    free(th->tabela); //libera a tabela
    free(th); //libera a tabela hash
}

void leitosDestruir(ListaLeitos* ll) {
    free(ll); //libera a lista de leitos
}

//FUNÇÕES AUXILIARES USADAS SOMENTE PRA TESTES E DEPURAÇÃO
//AUX PRINTAR CONTEUDO TABELA HASH
void tabelaHashPrintar(TabelaHash* th) {
    for (int i = 0; i < th->tamanho; i++) {
        printf("Indice %d: ", i); 
        No* atual = th->tabela[i];
        if (atual == NULL) {
            printf("null\n"); //se o index for vazio, printa null
        } else {
            while (atual) { //itera nos nos da lista
                printf("ID: %s, Nome: %s] -> ", atual->paciente.id, atual->paciente.nomeCompleto); //exibe o paciente
                atual = atual->proximo; //avança pro proximo no
            }
            printf("NULL\n");
        }
    }
}
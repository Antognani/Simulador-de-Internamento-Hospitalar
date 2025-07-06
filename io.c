#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

static FILE* arquivoLog = NULL; //variável global para o arquivo de log

//carrega os pacientes do arquivo CSV para a tabela hash
void carregarPacientesCSV(const char* nomeArquivo, TabelaHash* th) { 
    FILE* arquivo = fopen(nomeArquivo, "r"); //abre o arquivo CSV para leitura
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    char linha[256]; //buffer para ler cada linha do arquivo
    fgets(linha, sizeof(linha), arquivo);//ignora o header

    while (fgets(linha, sizeof(linha), arquivo)) { //lê cada linha do arquivo
        Paciente pac; //cria uma variável do tipo Paciente para armazenar os dados
        char* token; // ponteiro para armazenar os tokens extraídos da linha

        token = strtok(linha, ";"); //separa a linha pelo delimitador ';'
        if (token) strcpy(pac.id, token); //copia o ID do paciente 

        //faz o mesmo para todos os outros (então não precisa de comentarios)

        token = strtok(NULL, ";");
        if (token) strcpy(pac.nomeCompleto, token);

        token = strtok(NULL, ";");
        if (token) pac.idade = atoi(token);

        token = strtok(NULL, ";");
        if (token) pac.sexo = token[0];

        token = strtok(NULL, ";");
        if (token) strcpy(pac.cpf, token);

        token = strtok(NULL, ";");
        if (token) pac.prioridade = atoi(token);

        token = strtok(NULL, "\n");
        if (token) pac.atendido = atoi(token);

        tabelaHashInserir(th, pac); //insere o paciente na tabela hash
    }
    fclose(arquivo); //fecha o arquivo após a leitura
}

//inicia o log, abre o arquivo de log para escrita
void logIniciar(const char* nomeArquivo) { 
    arquivoLog = fopen(nomeArquivo, "w"); //abre o arquivo de log para escrita
    if (arquivoLog == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de log %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
}

//registra um evento no log com os detalhes
void logRegistrar(const char* evento, const char* detalhes) {
    char mensagem[256]; //buffer para armazenar a mensagem formatada
    sprintf(mensagem, "[%-10s] %s\n", evento, detalhes); //formata a mensagem com o evento e os detalhes

    printf("%s", mensagem); //printa a mensagem no console

    if (arquivoLog) {
        fprintf(arquivoLog, "%s", mensagem); //escreve a mensagem no arquivo de log
        fflush(arquivoLog); //garante que a mensagem seja escrita imediatamente
    }
}

//fecha o arquivo de log, se estiver aberto
void logFechar() { 
    if (arquivoLog) {
        fclose(arquivoLog); //fecha o arquivo de log
        arquivoLog = NULL; //define o ponteiro do arquivo de log como NULL
    }
}

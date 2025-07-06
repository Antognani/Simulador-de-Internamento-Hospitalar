#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

static FILE* arquivoLog = NULL;

void carregarPacientesCSV(const char* nomeArquivo, TabelaHash* th) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo);//ignora o header

    while (fgets(linha, sizeof(linha), arquivo)) {
        Paciente pac;
        char* token;

        token = strtok(linha, ";");
        if (token) strcpy(pac.id, token);

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

        tabelaHashInserir(th, pac);
    }
    fclose(arquivo);
}

void logIniciar(const char* nomeArquivo) {
    arquivoLog = fopen(nomeArquivo, "w");
    if (arquivoLog == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de log %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
}

void logRegistrar(const char* evento, const char* detalhes) {
    char mensagem[256];
    sprintf(mensagem, "[%-10s] %s\n", evento, detalhes);

    printf("%s", mensagem);

    if (arquivoLog) {
        fprintf(arquivoLog, "%s", mensagem);
        fflush(arquivoLog);
    }
}

void logFechar() {
    if (arquivoLog) {
        fclose(arquivoLog);
        arquivoLog = NULL;
    }
}

#include "log.h"

static FILE* arquivo_log = NULL;

void log_iniciar(const char* nome_arquivo) {
    arquivo_log = fopen(nome_arquivo, "w");
    if (arquivo_log == NULL) {
        perror("Erro ao abrir arquivo de log");
    }
}

void log_registrar(const char* mensagem) {
    // Imprime no terminal
    printf("%s", mensagem);
    // Grava no arquivo
    if (arquivo_log != NULL) {
        fprintf(arquivo_log, "%s", mensagem);
        fflush(arquivo_log); // Garante que a escrita seja feita imediatamente
    }
}
// ...
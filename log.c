#include "log.h"

static FILE* arquivo_log = NULL; // inicializa o ponteiro do arq como null pra evitar erro de acesso

void log_iniciar(const char* nome_arquivo) {
    arquivo_log = fopen(nome_arquivo, "w"); //abre o arquivo pra escrita
    if (arquivo_log == NULL) {
        perror("Erro ao abrir arquivo de log");
    }
}

void log_registrar(const char* mensagem) 
    printf("%s", mensagem); //printa terminal
    // Grava no arquivo
    if (arquivo_log != NULL) {
        fprintf(arquivo_log, "%s", mensagem);
        fflush(arquivo_log); // garante que a escrita seja feita imediatamente
    }
}

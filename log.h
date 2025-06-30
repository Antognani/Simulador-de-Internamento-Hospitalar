#ifndef LOG_H
#define LOG_H

#include <stdio.h>

void log_registrar(const char* mensagem);
void log_iniciar(const char* nome_arquivo);
void log_fechar();

#endif // LOG_H
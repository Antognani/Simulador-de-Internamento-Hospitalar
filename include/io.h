#ifndef IO_H
#define IO_H

#include "estruturas.h"

void carregarPacientesCSV(const char* nomeArquivo, TabelaHash* th);
void logIniciar(const char* nomeArquivo);
void logRegistrar(const char* evento, const char* detalhes);
void logFechar();

#endif
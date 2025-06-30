#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct Paciente {
    char id[7];
    char nomeCompleto[100];
    int idade;
    char sexo;
    char cpf[12]; //cpf como string e sem pontuação pra evitar problema de formatação
    int prioridade;
    int atendido;
} Paciente;

#endif // PACIENTE_H
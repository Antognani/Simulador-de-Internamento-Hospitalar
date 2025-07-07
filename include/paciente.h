#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct Paciente {
    char id[7]; //id do paciente, 6 caracteres + 1 pra \n
    char nomeCompleto[100];
    int idade;
    char sexo;
    char cpf[12]; //cpf como string e sem pontuação pra evitar problema de formatação +1 pro \n
    int prioridade;
    int atendido;
    int ciclosInternado;
} Paciente;

#endif // PACIENTE_H
# Simulador de Internamento Hospitalar
Projeto para construção de um sistema automático para gerenciar os internamentos em um hospital. Projeto final da matéria Estruturas de Dados Básicas I na UFRN.

Foi feito o uso de camelCase para nomear variáveis e funções.
Para executar, utilizar:
make
./bin/hospital

Repositório github: https://github.com/Antognani/Simulador-de-Internamento-Hospitalar

O projeto foi modularizado da seguinte maneira:

/hospital/

|

| include / simulacao.h - estruturas.h - paciente.h - io.h

| src / simulacao.c - estruturas.c - io.c - main.c

| makefile

| pacientes.csv


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para a função sleep()
#include <time.h>

#include "simulacao.h"
#include "estruturas.h" // Precisa manipular as estruturas
#include "io.h"        // Precisa registrar os eventos

#define CAPACIDADE_LEITOS 10
#define CAPACIDADE_DEQUE 20
#define ARQUIVO_PACIENTES "pacientes.csv"
#define ARQUIVO_LOG "processamento.log"
#define TEMPO_CICLO 2 //segundos
#define CHANCE_PERCENTUAL_ALTA 50

void iniciarSimulacao() {

    srand(time(NULL)); //inicia o gerador de números aleatórios
    logIniciar(ARQUIVO_LOG); //inicia o log
    printf("Simulação iniciada.\n");
    logRegistrar("INICIO", "Simulação iniciada.");

    //criar as estruturas
    Pilha* pilhaAltas = pilhaIniciar();
    Deque* filaEspera = dequeIniciar(CAPACIDADE_DEQUE);
    TabelaHash* thPacientes = tabelaHashIniciar(10); 
    ListaLeitos* leitos = LeitosIniciar();

    carregarPacientesCSV(ARQUIVO_PACIENTES, thPacientes);
    logRegistrar("INFO", "Pacientes carregados do arquivo CSV.");

    int ciclo = 1;
    int todosPacientesAlta = 0;

    while (!todosPacientesAlta || !dequeEstaVazio(filaEspera) || !leitosEstaVazio(leitos)) {
        leitosIncrementarCiclos(leitos); //incrementa o contador de ciclos internado para cada paciente
        char detalhesCiclo[100]; //aumentei para 100 para evitar overflow
        snprintf(detalhesCiclo, sizeof(detalhesCiclo), "---------------- CICLO %02d ----------------", ciclo);
        logRegistrar("CICLO", detalhesCiclo);

        if(!leitosEstaVazio(leitos) && leitosTemPacienteAptoAlta(leitos)) {
            if ((rand() % 100) < CHANCE_PERCENTUAL_ALTA) {
                Paciente pacienteAlta = leitosRemoverAleatorio(leitos);
                pilhaPush(pilhaAltas, pacienteAlta);
                
                char detalhesAlta[160]; //aumentei para 160 para evitar overflow
                snprintf(detalhesAlta, sizeof(detalhesAlta), "%s (%s)", pacienteAlta.id, pacienteAlta.nomeCompleto);
                logRegistrar("ALTA", detalhesAlta);
            }
        }

        if (!dequeEstaCheio(filaEspera) && !todosPacientesAlta) {
            Paciente* pacienteSorteado = tabelaHashSorteioPacNaoAtendido(thPacientes);
            if (pacienteSorteado) {
                pacienteSorteado->atendido = 1; //marca como atendido
                Paciente pacienteSorteadoCopy = *pacienteSorteado; //copia o paciente sorteado

                char detalhesSorteio[160]; //aumentei para 160 para evitar overflow
                snprintf(detalhesSorteio, sizeof(detalhesSorteio), "%s (%s)", pacienteSorteadoCopy.id, pacienteSorteadoCopy.nomeCompleto);
                logRegistrar("ESPERA", detalhesSorteio);

                if (pacienteSorteadoCopy.prioridade >= 4) {
                    dequeInserirCabeca(filaEspera, pacienteSorteadoCopy);
                } else {
                    dequeInserirFim(filaEspera, pacienteSorteadoCopy);
                }
            } else {
                todosPacientesAlta = 1; //se não há mais pacientes na tabela hash,
                logRegistrar("FIM", "Todos os pacientes já entraram na fila de espera ou foram atendidos.");
            }
        }

        if(!leitosEstaCheio(leitos) && !dequeEstaVazio(filaEspera)) {
            Paciente pacienteInternar = dequeRemoverPorPrioridade(filaEspera);
            pacienteInternar.ciclosInternado = 0; //inicializa o contador de ciclos internado
            LeitosAdicionar(leitos, pacienteInternar);

            char detalhesInternacao[160]; //aumentei para 160 para evitar overflow
            snprintf(detalhesInternacao, sizeof(detalhesInternacao), "%s (%s)", pacienteInternar.id, pacienteInternar.nomeCompleto);
            logRegistrar("INTERNADO", detalhesInternacao);
        }
        
        printf("\n");
        fflush(stdout); // Limpa o buffer de saída
        sleep(TEMPO_CICLO); // Pausa a execução por TEMPO_CICLO segundos
        ciclo++;
    }

    logRegistrar("FIM", "Simulação concluída. Todos os pacientes foram atendidos e altas foram processadas.");
    logFechar(); // Fecha o log

    tabelaHashDestruir(thPacientes);
    dequeDestruir(filaEspera);
    pilhaDestruir(pilhaAltas);
    leitosDestruir(leitos);

    printf("Simulação concluída. Log salvo.\n");

}
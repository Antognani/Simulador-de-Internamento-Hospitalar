#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //pra função sleep()
#include <time.h> //pra manipulação de tempo

#include "simulacao.h"
#include "estruturas.h"
#include "io.h"

#define CAPACIDADE_LEITOS 10
#define CAPACIDADE_DEQUE 20
#define ARQUIVO_PACIENTES "pacientes.csv"
#define ARQUIVO_LOG "processamento.log"
#define TEMPO_CICLO 2 //segundos
#define CHANCE_PERCENTUAL_ALTA 50 //50% de chance de alta

void iniciarSimulacao() {

    srand(time(NULL)); //inicia o gerador de números aleatórios
    logIniciar(ARQUIVO_LOG); //inicia o log
    printf("Simulação iniciada.\n");
    logRegistrar("INICIO", "Simulação iniciada.");

    //criar as estruturas
    Pilha* pilhaAltas = pilhaIniciar(); //inicializa a pilha de altas
    Deque* filaEspera = dequeIniciar(CAPACIDADE_DEQUE); //cria o deque com capacidade máxima de 20 pacientes
    TabelaHash* thPacientes = tabelaHashIniciar(10); //cria a tabela hash com tamanho 10
    ListaLeitos* leitos = LeitosIniciar(); //inicializa a lista de leitos

    carregarPacientesCSV(ARQUIVO_PACIENTES, thPacientes); //carrega os pacientes do arquivo CSV pra tabela hash
    logRegistrar("OBS", "Pacientes carregados do arquivo CSV.");

    int ciclo = 1; //contador de ciclos
    int todosPacientesAlta = 0; //flag para verificar se todos os pacientes já receberam alta

    //verifica se a tabela hash está vazia
    while (!todosPacientesAlta || !dequeEstaVazio(filaEspera) || !leitosEstaVazio(leitos)) {
        leitosIncrementarCiclos(leitos); //incrementa o contador de ciclos internado para cada paciente
        char detalhesCiclo[100]; //aumentei para 100 para evitar overflow
        snprintf(detalhesCiclo, sizeof(detalhesCiclo), "[CICLO %02d]", ciclo);
        logRegistrar("", detalhesCiclo); //registra o inicio do ciclo

        //verifica se há pacientes aptos para alta
        if(!leitosEstaVazio(leitos) && leitosTemPacienteAptoAlta(leitos)) {
            if ((rand() % 100) < CHANCE_PERCENTUAL_ALTA) { //lógica: rand gera um num aleatório, se for menor que 50, o paciente recebe alta (probabilidade de 50%)
                Paciente pacienteAlta = leitosRemoverAleatorioApto(leitos); //remove um paciente aleatório apto para alta
                pilhaPush(pilhaAltas, pacienteAlta); //adiciona o paciente à pilha de altas
                
                char detalhesAlta[160]; //aumentei para 160 para evitar overflow
                snprintf(detalhesAlta, sizeof(detalhesAlta), "%s (%s)", pacienteAlta.id, pacienteAlta.nomeCompleto); //copia os detalhes do paciente alta
                logRegistrar("ALTA", detalhesAlta); //registra a alta do paciente
            }
        }

        if (!dequeEstaCheio(filaEspera) && !todosPacientesAlta) { //verifica se a fila de espera não está cheia e se ainda há pacientes não atendidos
            Paciente* pacienteSorteado = tabelaHashSorteioPacNaoAtendido(thPacientes); //sorteia um paciente da tabela hash
            //se o paciente sorteado não for NULL, significa que ainda há pacientes não atendidos
            //se for NULL, significa que todos os pacientes já foram atendidos ou estão na fila
            if (pacienteSorteado) {
                pacienteSorteado->atendido = 1; //marca como atendido
                Paciente pacienteSorteadoCopy = *pacienteSorteado; //copia o paciente sorteado

                char detalhesSorteio[160]; //aumentei para 160 para evitar overflow
                snprintf(detalhesSorteio, sizeof(detalhesSorteio), "%s (prioridade %d)", pacienteSorteadoCopy.id, pacienteSorteadoCopy.prioridade); //copia os detalhes do paciente sorteado
                logRegistrar("ESPERA", detalhesSorteio);

                if (pacienteSorteadoCopy.prioridade > 4 || pacienteSorteadoCopy.prioridade == 4) { //se a prioridade for 4 ou 5, adiciona ao início da fila de espera
                    //IMPORTANTE: NÃO usar >=4 ou >3 porque ocorre Segmentation Fault (core dumped)!!!!!
                    dequeInserirCabeca(filaEspera, pacienteSorteadoCopy); //adiciona o paciente ao início da fila de espera
                } else {
                    dequeInserirFim(filaEspera, pacienteSorteadoCopy); //adiciona o paciente ao final da fila de espera
                }
            } else {
                todosPacientesAlta = 1; //se não tiver mais pacientes na tabela hash
                logRegistrar("FIM", "Não há mais pacientes para entrar na fila de espera.");
            }
        }

        if(!leitosEstaCheio(leitos) && !dequeEstaVazio(filaEspera)) {
            Paciente pacienteInternar = dequeRemoverPorPrioridade(filaEspera);
            pacienteInternar.ciclosInternado = 0; //inicializa o contador de ciclos internado
            LeitosAdicionar(leitos, pacienteInternar); //adiciona o paciente aos leitos

            char detalhesInternacao[160]; //aumentei para 160 para evitar overflow
            snprintf(detalhesInternacao, sizeof(detalhesInternacao), "%s (prioridade %d)", pacienteInternar.id, pacienteInternar.prioridade); //copia o paciente internado
            logRegistrar("INTERNADO", detalhesInternacao); //registra a internação
        }
        
        printf("\n");
        fflush(stdout); // limpa o buffer de saída
        sleep(TEMPO_CICLO); // pausa a execução por 2 segundos
        ciclo++;
    }

    logRegistrar("FIM", "Simulação concluída. Todos os pacientes foram atendidos e altas foram processadas.");
    logFechar(); // fecha o log

    tabelaHashDestruir(thPacientes);
    dequeDestruir(filaEspera);
    pilhaDestruir(pilhaAltas);
    leitosDestruir(leitos);

    printf("Simulação concluída. Log salvo.\n");

}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

double uniforme(){
    double u = rand() / ((double) RAND_MAX + 1);
    //u == 0 --> ln(u) <-- problema
    //limitando u entre (0,1]
    u = 1.0 - u;
    return u;
}

double gera_tempo(double l){
    return (-1.0/l) * log(uniforme());
}

double min(double n1, double n2){
    if (n1 < n2) return n1;
    return n2;
}

int main(){
    srand(time(NULL));
    double parametro_chegada;
    printf("Informe o tempo médio entre as chegadas (s): ");
    scanf("%lF", &parametro_chegada);
    parametro_chegada = 1.0/parametro_chegada;

    double parametro_saida;
    printf("Informe o tempo médio de atendimento (s): ");
    scanf("%lF", &parametro_saida);
    parametro_saida = 1.0/parametro_saida;

    double tempo_simulacao;
    printf("Informe o tempo de simulacao (s): ");
    scanf("%lF", &tempo_simulacao);

    double tempo_decorrido = 0.0;

    double tempo_chegada = gera_tempo(parametro_chegada);
    double tempo_saida = DBL_MAX;

    unsigned long int fila = 0;
    unsigned long int fila_max = 0;

    double soma_ocupacao = 0.0;


    while(tempo_decorrido <= tempo_simulacao){
        tempo_decorrido = 
            min(tempo_chegada, tempo_saida);

        //chegada
        if(tempo_decorrido == tempo_chegada){
            //sistema esta ocioso?
            if(!fila){
                tempo_saida =
                tempo_decorrido +
                gera_tempo(parametro_saida);

                soma_ocupacao += tempo_saida - 
                tempo_decorrido;
            }
            fila++;
            fila_max = fila > fila_max?
                fila:
                fila_max;

            tempo_chegada =
            tempo_decorrido +
            gera_tempo(parametro_chegada);
        }else{
            fila--;
            tempo_saida = DBL_MAX;
            //tem mais requisicoes na fila?
            if(fila){
                tempo_saida =
                tempo_decorrido +
                gera_tempo(parametro_saida);

                soma_ocupacao += tempo_saida - 
                tempo_decorrido;
            }
        }
    }

    printf("Maior tamanho de fila alcancado: %d\n",fila_max);
    printf("Ocupacao: %lF\n",soma_ocupacao/tempo_decorrido);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ANDARES 300
#define NUM_ELEVADORES 15

typedef struct {
    int localizacao;
    int esta_parado;
    int direcao;
} Elevador;

Elevador encontrarMelhorElevador(Elevador *predios, int numAndares, Elevador *chamadas, int numChamadas) {
    Elevador elevadorSelecionado = predios[0];
    int FS = 1;
    int i, j;

    for (i = 0; i < numAndares; i++) {
        int d = abs(predios[i].localizacao - chamadas[0].localizacao);
        int novoFS;

        if (predios[i].esta_parado) {
            novoFS = numAndares + 1 - d;
        } else if (predios[i].direcao == -1) {
            if (chamadas[0].localizacao > predios[i].localizacao) {
                novoFS = 1;
            } else if (chamadas[0].localizacao < predios[i].localizacao && chamadas[0].direcao == -1) {
                novoFS = numAndares + 2 - d;
            } else {
                novoFS = numAndares + 1 - d;
            }
        } else if (predios[i].direcao == 1) {
            if (chamadas[0].localizacao < predios[i].localizacao) {
                novoFS = 1;
            } else if (chamadas[0].localizacao > predios[i].localizacao && chamadas[0].direcao == 1) {
                novoFS = numAndares + 2 - d;
            } else {
                novoFS = numAndares + 1 - d;
            }
        }

        for (j = 1; j < numChamadas; j++) {
            d = abs(predios[i].localizacao - chamadas[j].localizacao);

            if (predios[i].esta_parado) {
                novoFS += numAndares + 1 - d;
            } else if (predios[i].direcao == -1) {
                if (chamadas[j].localizacao > predios[i].localizacao) {
                    novoFS += 1;
                } else if (chamadas[j].localizacao < predios[i].localizacao && chamadas[j].direcao == -1) {
                    novoFS += numAndares + 2 - d;
                } else {
                    novoFS += numAndares + 1 - d;
                }
            } else if (predios[i].direcao == 1) {
                if (chamadas[j].localizacao < predios[i].localizacao) {
                    novoFS += 1;
                } else if (chamadas[j].localizacao > predios[i].localizacao && chamadas[j].direcao == 1) {
                    novoFS += numAndares + 2 - d;
                } else {
                    novoFS += numAndares + 1 - d;
                }
            }
        }

        if (novoFS > FS) {
            elevadorSelecionado = predios[i];
            FS = novoFS;
        }
    }

    return elevadorSelecionado;
}

void exibirLocalizacaoElevadores(Elevador *predios, int numElevadores) {
    int i;
    printf("Localização dos Elevadores:\n");
    for (i = 0; i < numElevadores; i++) {
        printf("Elevador %d: Andar %d\n", i + 1, predios[i].localizacao);
    }
    printf("\n\n");
}

void moverElevador(Elevador *elevador, int destino) {

    int numAndares = NUM_ANDARES;
    if (destino < 1) {
        destino = 1;
    } else if (destino > numAndares) {
        destino = numAndares;
    }

    if (elevador->localizacao < destino) {
        printf("Elevador está subindo\n");
        while (elevador->localizacao < destino) {
            elevador->localizacao++;
            usleep(5000);
            printf("Andar Atual: %d\n", elevador->localizacao);
        }
    } else if (elevador->localizacao > destino) {
        printf("Elevador está descendo\n");
        while (elevador->localizacao > destino) {
            elevador->localizacao--;
            usleep(5000);
            printf("Andar Atual: %d\n", elevador->localizacao);
        }
    }

    printf("Elevador chegou ao andar de destino\n");
    elevador->esta_parado = 1;
}

int main() {
    Elevador predios[NUM_ELEVADORES];
    int numAndares = NUM_ANDARES;
    int i, chamada;
    int andarDestino;

    for (i = 0; i < NUM_ELEVADORES; i++) {
        predios[i].localizacao = rand() % numAndares + 1;
        predios[i].esta_parado = rand() % 2;
        predios[i].direcao = rand() % 3 - 1;
    }


    while (1){

    exibirLocalizacaoElevadores(predios, NUM_ELEVADORES);

    int numChamadas;
    printf("Digite o número de chamadas: ");
    scanf("%d", &numChamadas); getchar();

    Elevador chamadas[numChamadas];

    for (i = 0; i < numChamadas; i++) {

        printf("Digite a localização da chamada %d : ", i + 1);
        scanf("%d", &chamada); 
        if (chamada  == -1) return 0;
        chamadas[i].localizacao = chamada;


        printf("Digite o andar de destino da chamada : ");
        scanf("%d", &andarDestino);

        Elevador elevadorSelecionado = encontrarMelhorElevador(predios, numAndares, chamadas, numChamadas);
        printf("Localização do elevador selecionado: %d\n", elevadorSelecionado.localizacao);
        moverElevador(&elevadorSelecionado, andarDestino);

        // Atualizando a posição do elevador no array predios
         elevadorSelecionado.localizacao = andarDestino;
            
        }
      }
    
    return 0;
}

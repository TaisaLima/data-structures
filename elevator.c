#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_ANDARES 300
#define NUM_ELEVADORES 15
#define NUM_CORREDORES 3

typedef struct Elevador{
    int id;
    int andar;
    int corredor;
    int esta_parado;
} Elevador;

Elevador elevadores[NUM_ELEVADORES];

void initElevadores(){
    srand(time(NULL)); // Inicializa a semente de geração de números aleatórios
    for (int i = 0; i < NUM_ELEVADORES; i++) {
        elevadores[i].id = i;
        elevadores[i].andar = rand() % (NUM_ANDARES + 1);
        elevadores[i].corredor = rand() % (NUM_CORREDORES + 1);
        elevadores[i].esta_parado = 1;
    }
}




int encontrarMelhorElevador(int andar){
    int elevadorMenosDistante, menorDistancia;
    menorDistancia = 300;
    for (int i =0; i< NUM_ELEVADORES; i++){
        if(abs(elevadores[i].andar-andar) < menorDistancia){
            menorDistancia = abs(elevadores[i].andar-andar);
            elevadorMenosDistante = i;
        }
    }
    printf("Elevador %d Andar %d Distancia %d Corredor: %d \n\n", elevadorMenosDistante, elevadores[elevadorMenosDistante].andar, menorDistancia, elevadores[elevadorMenosDistante].corredor);
    return elevadorMenosDistante;
}

// Elevador encontrarMelhorElevador(Elevador *predios, int numAndares, Elevador *chamadas, int numChamadas) {
//     Elevador elevadorSelecionado = predios[0];
//     int FS = 1;
//     int i, j;

//     for (i = 0; i < numAndares; i++) {
//         int d = abs(predios[i].localizacao - chamadas[0].localizacao);
//         int novoFS;

//         if (predios[i].esta_parado) {
//             novoFS = numAndares + 1 - d;
//         } else if (predios[i].direcao == -1) {
//             if (chamadas[0].localizacao > predios[i].localizacao) {
//                 novoFS = 1;
//             } else if (chamadas[0].localizacao < predios[i].localizacao && chamadas[0].direcao == -1) {
//                 novoFS = numAndares + 2 - d;
//             } else {
//                 novoFS = numAndares + 1 - d;
//             }
//         } else if (predios[i].direcao == 1) {
//             if (chamadas[0].localizacao < predios[i].localizacao) {
//                 novoFS = 1;
//             } else if (chamadas[0].localizacao > predios[i].localizacao && chamadas[0].direcao == 1) {
//                 novoFS = numAndares + 2 - d;
//             } else {
//                 novoFS = numAndares + 1 - d;
//             }
//         }

//         for (j = 1; j < numChamadas; j++) {
//             d = abs(predios[i].localizacao - chamadas[j].localizacao);

//             if (predios[i].esta_parado) {
//                 novoFS += numAndares + 1 - d;
//             } else if (predios[i].direcao == -1) {
//                 if (chamadas[j].localizacao > predios[i].localizacao) {
//                     novoFS += 1;
//                 } else if (chamadas[j].localizacao < predios[i].localizacao && chamadas[j].direcao == -1) {
//                     novoFS += numAndares + 2 - d;
//                 } else {
//                     novoFS += numAndares + 1 - d;
//                 }
//             } else if (predios[i].direcao == 1) {
//                 if (chamadas[j].localizacao < predios[i].localizacao) {
//                     novoFS += 1;
//                 } else if (chamadas[j].localizacao > predios[i].localizacao && chamadas[j].direcao == 1) {
//                     novoFS += numAndares + 2 - d;
//                 } else {
//                     novoFS += numAndares + 1 - d;
//                 }
//             }
//         }

//         if (novoFS > FS) {
//             elevadorSelecionado = predios[i];
//             FS = novoFS;
//         }
//     }

//     return elevadorSelecionado;
// }

void exibirLocalizacaoElevadores() {
    printf("\n\nLocalização dos Elevadores:\n");

    for (int andar = NUM_ANDARES; andar> 0; andar--) {
        for (int corredor = 1; corredor <= NUM_CORREDORES; corredor++) {
            int elevadorPresente = 0;
            for (int i = 0; i < NUM_ELEVADORES; i++) {
                if (elevadores[i].andar == andar && elevadores[i].corredor == corredor) {
                    printf("%-15d", i);
                    elevadorPresente = 1;
                    break;
                }
            }
            if (!elevadorPresente) {
                printf("%-15s", "..");
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("  tunel 1       tunel 2       tunel 3\n");
    printf("\n");
}


void colisao (int idElevador,int destino, int buscar){

    int corredor = elevadores[idElevador].corredor; int andar = elevadores[idElevador].andar;

    if ( andar > buscar){
        for (int j = andar; j>0; j-- ){

             for (int i = 0; i < NUM_ELEVADORES; i++) {
                
                if (elevadores[i].andar == j && elevadores[i].corredor == corredor) {
                    
    int fran = (corredor + 1) %3;
                    elevadores[i].corredor =  fran;
                    
                    printf ("\n\n Colisao resolvida. Movemos o elevador %d para o corredor %d \n\n", i, fran); getchar(); 

                }
            }

        }
    }

    if ( andar > destino){
        for (int j = andar; j>0; j-- ){

             for (int i = 0; i < NUM_ELEVADORES; i++) {
                
                if (elevadores[i].andar == j && elevadores[i].corredor == corredor) {
                    int fran = (corredor + 1) %3;
                    elevadores[i].corredor =  fran;
                    
                    printf ("\n\n Colisao resolvida. Movemos o elevador %d para o corredor %d \n\n", i, fran); getchar(); 

                }
            }

        }
    }

    if ( andar < destino){
        for (int j = 0; j< andar; j++ ){

             for (int i = 0; i < NUM_ELEVADORES; i++) {
                
                if (elevadores[i].andar == j && elevadores[i].corredor == corredor) {
                    
                    int fran = (corredor + 1) %3;
                    elevadores[i].corredor =  fran;
                    
                    printf ("\n\n Colisao resolvida. Movemos o elevador %d para o corredor %d \n\n", i, fran); getchar(); 


                }
            }

        }
    }

     if ( andar < buscar){
        for (int j = 0; j< andar; j++ ){

             for (int i = 0; i < NUM_ELEVADORES; i++) {
                
                if (elevadores[i].andar == j && elevadores[i].corredor == corredor) {
                    
    
              int fran = (corredor + 1) %3;
                    elevadores[i].corredor =  fran;
                    
                    printf ("\n\n Colisao resolvida. Movemos o elevador %d para o corredor %d \n\n", i-1, fran); getchar(); 

                }
            }

        }
    }

}



void moverElevador(int idElevador, int destino) {

    int numAndares = NUM_ANDARES;
  

    if (elevadores[idElevador].andar < destino) {
    
            while (elevadores[idElevador].andar != destino +1){
              elevadores[idElevador].andar++;
             
            }

        } else if (elevadores[idElevador].andar > destino) {
        
        while (elevadores[idElevador].andar != destino +1){
            elevadores[idElevador].andar--;
           
        }
    }
    
    elevadores[idElevador].esta_parado = 1;
}

int main() {
    int numAndares = NUM_ANDARES;
    int i, chamada;
    int andarDestino;

    initElevadores();
    while (1){

        exibirLocalizacaoElevadores();
        char c;
        puts("Chamada?");
        scanf(" %c", &c);

        if(c=='y'){
            printf("Digite a localização: ");
            scanf("%d", &chamada); 
            if (chamada  == -1) return 0;


            printf("Digite o andar de destino da chamada : ");
            scanf("%d", &andarDestino);

            int idElevadorSelecionado = encontrarMelhorElevador(chamada);

            colisao(idElevadorSelecionado,andarDestino,chamada);

            moverElevador(idElevadorSelecionado, andarDestino);
            getchar(); getchar(); 
        } 
    }
    
    return 0;
}

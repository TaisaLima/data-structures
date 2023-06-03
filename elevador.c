#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

typedef struct {
    char* nome;
    int andar;
    int tunel;
} Elevador;


typedef struct {
    Elevador* e1 ;
    Elevador* e2 ;
    Elevador* e3 ;
    Elevador* e4 ;
    Elevador* e5 ;
    Elevador* e6 ;
    Elevador* e7 ;
    Elevador* e8 ;
    Elevador* e9 ;
    Elevador* e10 ;
    Elevador* e11 ;
    Elevador* e12 ;
    Elevador* e13 ;
    Elevador* e14 ;
    Elevador* e15 ;
    
} Tunel;

Elevador* criar_elevador(char* nome, int andar, int tunel) {
    Elevador* elevador = (Elevador*)malloc(sizeof(Elevador));
    elevador->nome = nome;
    elevador->andar = andar;
    elevador->tunel= tunel;
    return elevador;
}

int distance(Elevador* elevador, int andar) {
    return abs(elevador->andar - andar);
}

Tunel* criar_tunel(Elevador* e1, Elevador* e2, Elevador* e3, Elevador* e4, Elevador* e5) {
    Tunel* tunel = (Tunel*)malloc(sizeof(Tunel));
    tunel->e1 = e1;
    tunel->e2 = e2;
    tunel->e3 = e3;
    tunel->e4 = e4;
    tunel->e5 = e5;

    return tunel;
}

void sleep_milliseconds(int milliseconds) {
    usleep(milliseconds * 1000);
}


int melhor_elevador(Tunel* tunel, int andar) {
    int d1 = distance(tunel->e1, andar);
    int d2 = distance(tunel->e2, andar);
    int d3 = distance(tunel->e3, andar);
    int melhor = d1 < d2 ? (d1 < d3 ? d1 : d3) : (d2 < d3 ? d2 : d3);
    if (d1 == melhor) {
        return 1;
    } else if (d2 == melhor) {
        return 2;
    } else {
        return 3;
    }
}

Elevador* get_elevador(Tunel* tunel, int andar) {
    if (tunel->e1->andar == andar) {
        return tunel->e1;
    } else if (tunel->e2->andar == andar) {
        return tunel->e2;
    } else if (tunel->e3->andar == andar) {
        return tunel->e3;
    }
    return NULL;
}

int melhor_tunel(int andar, Tunel** tuneis) {
    int i, melhor = 300, tunel = 0;


    for (i = 0; i < 3; i++) {
        int d = melhor_elevador(tuneis[i], andar);
        if (d < melhor) {
            melhor = d;
            tunel = i;
        }
    }
    return tunel;
}

int prioridade(int* req, Tunel** tuneis) {
    int d = melhor_tunel(req[0], tuneis);
    return d;
}

int ler_entrada(int* req) {
    int atual, destino;
    printf("Andar da chamada: ");
    scanf("%d", &atual);
    if (atual == -1) return 1;
    printf("Andar de destino: ");
    scanf("%d", &destino);
    if (atual > 300 || destino > 300 || atual < 1 || destino < 0) {
        printf("Erro: Tente novamente\n");
        ler_entrada(req);
    }
    req[0] = atual;
    req[1] = destino;
    
    return 0;
}
void mudar_tunel(Tunel** tuneis, int tunel_origem, int tunel_destino, int andar) {
    Tunel* tunel1 = tuneis[tunel_origem];
    Tunel* tunel2 = tuneis[tunel_destino];

    Elevador* elevador = NULL;

    // Verifica se o elevador está no andar atual no túnel de origem
    if (tunel1->e1->andar == andar) {
        elevador = tunel1->e1;
    } else if (tunel1->e2->andar == andar) {
        elevador = tunel1->e2;
    } else if (tunel1->e3->andar == andar) {
        elevador = tunel1->e3;
    }

    if (elevador != NULL) {
        // Move o elevador para o túnel de destino
        if (tunel2->e1 == NULL) {
            tunel2->e1 = elevador;
        } else if (tunel2->e2 == NULL) {
            tunel2->e2 = elevador;
        } else if (tunel2->e3 == NULL) {
            tunel2->e3 = elevador;
        }

        // Remove o elevador do túnel de origem
        if (tunel1->e1 == elevador) {
            tunel1->e1 = NULL;
        } else if (tunel1->e2 == elevador) {
            tunel1->e2 = NULL;
        } else if (tunel1->e3 == elevador) {
            tunel1->e3 = NULL;
        }

        // Atualiza o túnel do elevador
        elevador->tunel = tunel_destino;
    }
}

int colisao(Tunel* tunel, int andar, Elevador* e) {
    
    if (tunel->e1->andar == andar && strcmp(tunel->e1->nome, e->nome) != 0) {
        return 1;
    } else if (tunel->e2->andar == andar && strcmp(tunel->e2->nome, e->nome) != 0) {
        return 1;
    } else if (tunel->e3->andar == andar && strcmp(tunel->e3->nome, e->nome) != 0) {
        return 1;
    } else if (tunel->e4->andar == andar && strcmp(tunel->e4->nome, e->nome) != 0) {
        return 1;
    } else if (tunel->e5->andar == andar && strcmp(tunel->e5->nome, e->nome) != 0) {
        return 1;
    }
    return 0;
}



void resolver_colisao(Tunel* tunel, int andar, Elevador* elevador, Tunel** tuneis) {
    Elevador* conflitado = get_elevador(tunel, andar);

    if (elevador->andar == conflitado->andar) {
        int tunel_origem = conflitado->tunel;
        int tunel_destino = (conflitado->tunel + 1) % 3; 

        mudar_tunel(tuneis, tunel_origem, tunel_destino, andar);
    }
}


void mover_elevador(int* req, Tunel** tuneis) {
    int andar = req[0];
    int destino = req[1];
    int tunel = melhor_tunel(andar, tuneis);
    Tunel* t = tuneis[tunel];
    int elevador_num = melhor_elevador(t, andar);

    Elevador* elevador = elevador_num == 1 ? t->e1 : (elevador_num == 2 ? t->e2 : t->e3);

    for (int i = andar; i>0 ; i--){
        int x = colisao(t, i, elevador);
        if ( x==1) {
          resolver_colisao(t, i, elevador, tuneis);
        }

    }

    int gasto = distance(elevador, andar);
    int custo = gasto + distance(elevador, destino);
    int tempo = (gasto * 2)/ 60;

    printf("\nO Elevador mais próximo é o %s, com uma distância de %d andares || tempo de espera é: %d min\n\n", elevador->nome, gasto, tempo);
    printf("%s indo de %d para %d buscar um cliente\n", elevador->nome, elevador->andar, andar);
    elevador->andar = andar;

    printf("%s indo de %d para %d deixar alguém || Gasto da operação: %d \n", elevador->nome, elevador->andar, destino, custo);
    elevador->andar = destino;
    printf("\n------------------------------\n");
}
void exibir_predio(Tunel** tuneis) {

    // Exibe o prédio com os andares e a posição atual dos elevadores
    for (int i = 300; i >= 1; i--) {
        printf("%-5d", i); // Exibe o número do andar

        for (int j = 0; j < 3; j++) {
            Tunel* tunel = tuneis[j];
            Elevador* elevador = NULL;

            // Verifica se o elevador está no andar atual
            if (tunel->e1->andar == i) {
                elevador = tunel->e1;
            } else if (tunel->e2->andar == i) {
                elevador = tunel->e2;
            } else if (tunel->e3->andar == i) {
                elevador = tunel->e3;
            }
            else if (tunel->e4->andar == i) {
                elevador = tunel->e4;
            } else if (tunel->e5->andar == i) {
                elevador = tunel->e5;
            }
           
            if (elevador != NULL) {
                printf("%-15s", elevador->nome);
            } else {
                printf("%-15s", ".");
            }
        }
        printf("\n");
    }

    // Exibe a base do prédio com os números dos andares
    printf("-----------------------------------------------------\n");
    printf("  tunel 1       tunel 2       tunel 3\n");
    printf("\n");
}

int main() {
    
    int opt = 0; 
    Elevador* e1 = criar_elevador("Elevador A1", 1, 1);
    
    Elevador* e2 = criar_elevador("Elevador B1", 150, 1);
    Elevador* e3 = criar_elevador("Elevador C1", 300, 1);
    Elevador* e4 = criar_elevador("Elevador D1", 200, 1);
    Elevador* e5 = criar_elevador("Elevador E1", 100, 1);
    Tunel* t1 = criar_tunel(e1, e2, e3, e4, e5);

    e1 = criar_elevador("Elevador A2", 2, 2);
    e2 = criar_elevador("Elevador B2", 250, 2);
    e3 = criar_elevador("Elevador C2", 200, 2);
    e4 = criar_elevador("Elevador D2", 100, 2);
    e5 = criar_elevador("Elevador E2", 300, 2);
    Tunel* t2 = criar_tunel(e1, e2, e3, e4, e5);


    e1 = criar_elevador("Elevador A3", 1, 3);
    e2 = criar_elevador("Elevador B3", 150, 3);
    e3 = criar_elevador("Elevador C3", 300, 3);
    e4 = criar_elevador("Elevador D3", 100, 3);
    e5 = criar_elevador("Elevador E3", 200, 3);
    Tunel* t3 = criar_tunel(e1, e2, e3, e4, e5);


    Tunel** tuneis = (Tunel**)malloc(3 * sizeof(Tunel*));
    tuneis[0] = t1;
    tuneis[1] = t2;
    tuneis[2] = t3;

    int reqs[100][2]; // Fila de prioridade
    int req_count = 0;
    
    while (1){
        
        exibir_predio(tuneis);

            while (1) {
                usleep(500000); 
                printf("\nTem chamada?\n[1] - SIM\n[2] - NÃO\n[-1] - ENCERRAR\n\n");
                scanf("%d", &opt); 
                if (opt == 1) {
                    ler_entrada(reqs[req_count]);
                    req_count++;
                }
                else if (opt == 2) {break;}
                else if (opt == -1) {return 0;}
            }
    

        for (int i = 0; i < req_count; i++) 
        {
            mover_elevador(reqs[i], tuneis);
            getchar();getchar();

        }
                
        req_count = 0;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char* nome;
    int andar;
} Elevador;

typedef struct {
    Elevador* e1;
    Elevador* e2;
    Elevador* e3;
    Elevador* e4;
    Elevador* e5;
    Elevador* e6;
    Elevador* e7;
    Elevador* e8;
    Elevador* e9;
    Elevador* e10;
    Elevador* e11;
    Elevador* e12;
    Elevador* e13;
    Elevador* e14;
    Elevador* e15;
} Tunel;

Elevador* criar_elevador(char* nome, int andar) {
    Elevador* elevador = (Elevador*)malloc(sizeof(Elevador));
    elevador->nome = nome;
    elevador->andar = andar;
    return elevador;
}

int distance(Elevador* elevador, int andar) {
    return abs(elevador->andar - andar);
}

Tunel* criar_tunel(Elevador* e1, Elevador* e2, Elevador* e3, Elevador* e4, Elevador* e5, Elevador* e6, Elevador* e7, Elevador* e8, Elevador* e9, Elevador* e10, Elevador* e11, Elevador* e12, Elevador* e13, Elevador* e14, Elevador* e15) {
    Tunel* tunel = (Tunel*)malloc(sizeof(Tunel));
    tunel->e1 = e1;
    tunel->e2 = e2;
    tunel->e3 = e3;
    tunel->e4 = e4;
    tunel->e5 = e5;
    tunel->e6 = e6;
    tunel->e7 = e7;
    tunel->e8 = e8;
    tunel->e9 = e9;
    tunel->e10 = e10;
    tunel->e11 = e11;
    tunel->e12 = e12;
    tunel->e13 = e13;
    tunel->e14 = e14;
    tunel->e15 = e15;
    return tunel;
}

int melhor_elevador(Tunel* tunel, int andar) {
    int d1 = distance(tunel->e1, andar);
    int d2 = distance(tunel->e2, andar);
    int d3 = distance(tunel->e3, andar);
    int d4 = distance(tunel->e4, andar);
    int d5 = distance(tunel->e5, andar);
    int d6 = distance(tunel->e6, andar);
    int d7 = distance(tunel->e7, andar);
    int d8 = distance(tunel->e8, andar);
    int d9 = distance(tunel->e9, andar);
    int d10 = distance(tunel->e10, andar);
    int d11 = distance(tunel->e11, andar);
    int d12 = distance(tunel->e12, andar);
    int d13 = distance(tunel->e13, andar);
    int d14 = distance(tunel->e14, andar);
    int d15 = distance(tunel->e15, andar);

    int min_dist = d1;
    int melhor_elevador = 1;

    if (d2 < min_dist) {
        min_dist = d2;
        melhor_elevador = 2;
    }
    if (d3 < min_dist) {
        min_dist = d3;
        melhor_elevador = 3;
    }
    if (d4 < min_dist) {
        min_dist = d4;
        melhor_elevador = 4;
    }
    if (d5 < min_dist) {
        min_dist = d5;
        melhor_elevador = 5;
    }
    if (d6 < min_dist) {
        min_dist = d6;
        melhor_elevador = 6;
    }
    if (d7 < min_dist) {
        min_dist = d7;
        melhor_elevador = 7;
    }
    if (d8 < min_dist) {
        min_dist = d8;
        melhor_elevador = 8;
    }
    if (d9 < min_dist) {
        min_dist = d9;
        melhor_elevador = 9;
    }
    if (d10 < min_dist) {
        min_dist = d10;
        melhor_elevador = 10;
    }
    if (d11 < min_dist) {
        min_dist = d11;
        melhor_elevador = 11;
    }
    if (d12 < min_dist) {
        min_dist = d12;
        melhor_elevador = 12;
    }
    if (d13 < min_dist) {
        min_dist = d13;
        melhor_elevador = 13;
    }
    if (d14 < min_dist) {
        min_dist = d14;
        melhor_elevador = 14;
    }
    if (d15 < min_dist) {
        min_dist = d15;
        melhor_elevador = 15;
    }

    return melhor_elevador;
}

void mover_elevador(int andar, Tunel* tunel) {
    int melhor_elev = melhor_elevador(tunel, andar);
    Elevador* elevador;

    switch (melhor_elev) {
        case 1:
            elevador = tunel->e1;
            break;
        case 2:
            elevador = tunel->e2;
            break;
        case 3:
            elevador = tunel->e3;
            break;
        case 4:
            elevador = tunel->e4;
            break;
        case 5:
            elevador = tunel->e5;
            break;
        case 6:
            elevador = tunel->e6;
            break;
        case 7:
            elevador = tunel->e7;
            break;
        case 8:
            elevador = tunel->e8;
            break;
        case 9:
            elevador = tunel->e9;
            break;
        case 10:
            elevador = tunel->e10;
            break;
        case 11:
            elevador = tunel->e11;
            break;
        case 12:
            elevador = tunel->e12;
            break;
        case 13:
            elevador = tunel->e13;
            break;
        case 14:
            elevador = tunel->e14;
            break;
        case 15:
            elevador = tunel->e15;
            break;
        default:
            return;
    }

    printf("Movendo %s para o andar %d\n", elevador->nome, andar);
    elevador->andar = andar;
}

void resolver_colisao(int andar, Tunel* tunel) {
    int melhor_elev = melhor_elevador(tunel, andar);
    Elevador* elevador;

    switch (melhor_elev) {
        case 1:
            elevador = tunel->e1;
            break;
        case 2:
            elevador = tunel->e2;
            break;
        case 3:
            elevador = tunel->e3;
            break;
        case 4:
            elevador = tunel->e4;
            break;
        case 5:
            elevador = tunel->e5;
            break;
        case 6:
            elevador = tunel->e6;
            break;
        case 7:
            elevador = tunel->e7;
            break;
        case 8:
            elevador = tunel->e8;
            break;
        case 9:
            elevador = tunel->e9;
            break;
        case 10:
            elevador = tunel->e10;
            break;
        case 11:
            elevador = tunel->e11;
            break;
        case 12:
            elevador = tunel->e12;
            break;
        case 13:
            elevador = tunel->e13;
            break;
        case 14:
            elevador = tunel->e14;
            break;
        case 15:
            elevador = tunel->e15;
            break;
        default:
            return;
    }

    printf("Colisão detectada no andar %d\n", andar);

    // Verifica se o elevador está no Túnel 1
    if (elevador == tunel->e1 || elevador == tunel->e2 || elevador == tunel->e3 || elevador == tunel->e4 || elevador == tunel->e5) {
        // Movendo o elevador para o próximo túnel (Túnel 2)
        if (melhor_elev < 11) {
            printf("Movendo %s para o próximo túnel\n", elevador->nome);
            tunel->e11 = elevador;
        } else {
            printf("Movendo %s para o próximo túnel\n", elevador->nome);
            tunel->e12 = elevador;
        }
    }

    // Verifica se o elevador está no Túnel 3
    if (elevador == tunel->e11 || elevador == tunel->e12 || elevador == tunel->e13 || elevador == tunel->e14 || elevador == tunel->e15) {
        // Movendo o elevador para o próximo túnel (Túnel 2)
        if (melhor_elev < 6) {
            printf("Movendo %s para o próximo túnel\n", elevador->nome);
            tunel->e6 = elevador;
        } else {
            printf("Movendo %s para o próximo túnel\n", elevador->nome);
            tunel->e5 = elevador;
        }
    }

    elevador->andar = andar;
}

void exibir_predio(Tunel* tunel) {
    for (int i = 0; i < 30; i++) {
        printf("|");

        for (int j = 1; j <= 15; j++) {
            if (i == tunel->e1->andar && j == 1) {
                printf(" E ");
            } else if (i == tunel->e2->andar && j == 2) {
                printf(" E ");
            } else if (i == tunel->e3->andar && j == 3) {
                printf(" E ");
            } else if (i == tunel->e4->andar && j == 4) {
                printf(" E ");
            } else if (i == tunel->e5->andar && j == 5) {
                printf(" E ");
            } else if (i == tunel->e6->andar && j == 6) {
                printf(" E ");
            } else if (i == tunel->e7->andar && j == 7) {
                printf(" E ");
            } else if (i == tunel->e8->andar && j == 8) {
                printf(" E ");
            } else if (i == tunel->e9->andar && j == 9) {
                printf(" E ");
            } else if (i == tunel->e10->andar && j == 10) {
                printf(" E ");
            } else if (i == tunel->e11->andar && j == 11) {
                printf(" E ");
            } else if (i == tunel->e12->andar && j == 12) {
                printf(" E ");
            } else if (i == tunel->e13->andar && j == 13) {
                printf(" E ");
            } else if (i == tunel->e14->andar && j == 14) {
                printf(" E ");
            } else if (i == tunel->e15->andar && j == 15) {
                printf(" E ");
            } else {
                printf("   ");
            }
        }

        printf("|\n");
    }
}

int main() {
    Elevador* e1 = criar_elevador("E1", 0);
    Elevador* e2 = criar_elevador("E2", 0);
    Elevador* e3 = criar_elevador("E3", 0);
    Elevador* e4 = criar_elevador("E4", 0);
    Elevador* e5 = criar_elevador("E5", 0);
    Elevador* e6 = criar_elevador("E6", 29);
    Elevador* e7 = criar_elevador("E7", 29);
    Elevador* e8 = criar_elevador("E8", 29);
    Elevador* e9 = criar_elevador("E9", 29);
    Elevador* e10 = criar_elevador("E10", 29);
    Elevador* e11 = criar_elevador("E11", 0);
    Elevador* e12 = criar_elevador("E12", 0);
    Elevador* e13 = criar_elevador("E13", 0);
    Elevador* e14 = criar_elevador("E14", 0);
    Elevador* e15 = criar_elevador("E15", 0);

    Tunel* tunel = criar_tunel(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);

    for (int i = 0; i < 30; i++) {
        int andar = i;

        // Movendo os elevadores
        if (andar % 10 == 0) {
            mover_elevador(andar, tunel);
        }

        // Verificando colisões
        if (andar == 10 || andar == 20) {
            resolver_colisao(andar, tunel);
        }

        // Exibindo o estado atual do prédio
        exibir_predio(tunel);
    }

    return 0;
}

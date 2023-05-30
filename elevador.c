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

Tunel* criar_tunel(Elevador* e1, Elevador* e2, Elevador* e3, Elevador* e4, Elevador* e5) {
    Tunel* tunel = (Tunel*)malloc(sizeof(Tunel));
    tunel->e1 = e1;
    tunel->e2 = e2;
    tunel->e3 = e3;
    tunel->e4 = e4;
    tunel->e5 = e5;

    return tunel;
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

int colisao(Tunel* tunel, int andar, Elevador* e) {
    if (tunel->e1->andar == andar && tunel->e1->nome != e->nome) {
        return 1;
    } else if (tunel->e2->andar == andar && tunel->e2->nome != e->nome) {
        return 1;
    } else if (tunel->e3->andar == andar && tunel->e3->nome != e->nome) {
        return 1;
    }
    return 0;
}

void resolver_colisao(Tunel* tunel, int andar, Elevador* elevador) {
    Elevador* conflitado = get_elevador(tunel, andar);
    if (elevador->andar < conflitado->andar) {
        printf("Subindo %s de %d até %d para evitar colisões\n", conflitado->nome, conflitado->andar, conflitado->andar + 1);
        conflitado->andar += 1;
    } else {
        printf("Descendo %s de %d até %d para evitar colisões\n", conflitado->nome, conflitado->andar, conflitado->andar - 1);
        conflitado->andar -= 1;
    }
}

int melhor_tunel(int andar, Tunel** tuneis) {
    int i;
    int melhor = 100000;
    int tunel = 0;
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

void mover_elevador(int* req, Tunel** tuneis) {
    int andar = req[0];
    int destino = req[1];
    int tunel = melhor_tunel(andar, tuneis);
    Tunel* t = tuneis[tunel];
    int elevador_num = melhor_elevador(t, andar);

    Elevador* elevador = elevador_num == 1 ? t->e1 : (elevador_num == 2 ? t->e2 : t->e3);
    if (colisao(t, andar, elevador)) {
        resolver_colisao(t, andar, elevador);
    }

    int gasto = distance(elevador, andar);

    printf("O Elevador mais próximo é o %s, com uma distância de %d andares || tempo de espera é: %d\n\n", elevador->nome, gasto, gasto);
    printf("%s indo de %d para %d buscar um cliente\n", elevador->nome, elevador->andar, andar);
    elevador->andar = andar;


    gasto += distance(elevador, destino);
    if (colisao(t, destino, elevador)) {
        resolver_colisao(t, destino, elevador);
    }
    printf("%s indo de %d para %d deixar alguém || Gasto da operação: %d \n", elevador->nome, elevador->andar, destino, gasto);
    elevador->andar = destino;
    printf("\n------------------------------\n");
}

int main() {
    
    int opt = 0; 
    Elevador* e1 = criar_elevador("Elevador A1", 1);
    Elevador* e2 = criar_elevador("Elevador B1", 150);
    Elevador* e3 = criar_elevador("Elevador C1", 300);
    Elevador* e4 = criar_elevador("Elevador D1", 200);
    Elevador* e5 = criar_elevador("Elevador E1", 100);
    Tunel* t1 = criar_tunel(e1, e2, e3, e4, e5);

    e1 = criar_elevador("Elevador A2", 2);
    e2 = criar_elevador("Elevador B2", 250);
    e3 = criar_elevador("Elevador C2", 200);
    e4 = criar_elevador("Elevador D2", 100);
    e5 = criar_elevador("Elevador E2", 300);
    Tunel* t2 = criar_tunel(e1, e2, e3, e4, e5);


    e1 = criar_elevador("Elevador A3", 1);
    e2 = criar_elevador("Elevador B3", 150);
    e3 = criar_elevador("Elevador C3", 300);
    e4 = criar_elevador("Elevador D3", 100);
    e5 = criar_elevador("Elevador E3", 200);
    Tunel* t3 = criar_tunel(e1, e2, e3, e4, e5);


    Tunel** tuneis = (Tunel**)malloc(3 * sizeof(Tunel*));
    tuneis[0] = t1;
    tuneis[1] = t2;
    tuneis[2] = t3;

    int reqs[100][2]; // Fila de prioridade
    int req_count = 0;
    
    while (1){
        
        while (1) {
            
        printf("\nTem chamada?\n[1] - SIM\n[2] - NÃO\n[-1] - ENCERRAR\n\n");
        scanf("%d", &opt);
        if (opt == 1) {
                
            ler_entrada(reqs[req_count]);
            req_count++;
         }
         else if (opt == 2) {break;}
         else if (opt == -1) {return 0;}
        }
    
        int i, j;
        for (i = 0; i < req_count - 1; i++) {
            for (j = i + 1; j < req_count; j++) {
                if (prioridade(reqs[i], tuneis) > prioridade(reqs[j], tuneis)) {
                    int temp[2];
                    temp[0] = reqs[i][0];
                    temp[1] = reqs[i][1];
                    reqs[i][0] = reqs[j][0];
                    reqs[i][1] = reqs[j][1];
                    reqs[j][0] = temp[0];
                    reqs[j][1] = temp[1];
                }
            }
        }
    
        for (i = 0; i < req_count; i++) {
            mover_elevador(reqs[i], tuneis);
        }
    }

    return 0;
}

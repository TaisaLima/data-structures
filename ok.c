#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[100];
    int prioridade;
} QueueItem;

typedef struct {
    QueueItem items[MAX];
    int capacity;
    int size;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue* queue, int capacity) {
    queue->capacity = capacity;
    queue->size = 0;
}

void enqueue(PriorityQueue* queue, char* nome, int prioridade) {
    
        if (queue->size == queue->capacity) {
        printf("Não conseguimos atender mais ninguém\n");
       return;
        }
    
    QueueItem item;
    strcpy(item.nome, nome);
    item.prioridade = prioridade;

    int i = queue->size - 1;
    while (i >= 0 && queue->items[i].prioridade > prioridade) {
        queue->items[i + 1] = queue->items[i];
        i--;
    }
    
    queue->items[i + 1] = item;
    queue->size++;

}

char* dequeue(PriorityQueue* queue) {
    if (queue->size == 0) {
        printf("Não há ninguém na fila\n");
        return NULL;
    }
    
    char* nome = queue->items[queue->size - 1].nome;
    queue->size--;
    return nome;
}

void printPriorityQueue(PriorityQueue* queue) {
    printf("Ordem de chamada: \n");
    printf("---------------\n");
    printf("(Caso queira retirar o paciente da vez, pressione 'f') \n\n");
    
    if (queue->size == 0) {
        printf("Vazia!\n");
        return;
    }
    
    for (int i = 0; i < queue->size; i++) {
        printf("Paciente: %s, Prioridade: %d, Tempo de espera: %d min \n", queue->items[i].nome, queue->items[i].prioridade, i * 30 );
    }
}

int main() {
    int capacidade, prioridade, ind=1;
    char nome[100];

    printf("Insira a quantidade de fichas que irão ser dadas na recepção: ");
    scanf("%d", &capacidade);
    getchar();  
    
    PriorityQueue queue;
    initializePriorityQueue(&queue, capacidade);

    printf("\n\nNeste hospital os pacientes recebem uma faixinha colorida na triagem de acordo com a sua prioridade. \n\n");
     printf("Prioridade 0: Faixa vermelha [crianças menores de 5 anos e idoso com mais de 80 anos] ");
     printf("\nPrioridade 1: Faixa amarela [crianças com mais de 5 anos, adolescentes menores de 16 anos e idosos entre 60 e 80 anos] ");
     printf("\nPrioridade 2: Faixa Verde [todas as outra pessoas]");
     printf("\nSendo assim, insira no sistema a prioridade de acordo com a faixa do paciente\n\n");

     while (1) {

        printf("insira o nome do paciente e seu nível de prioridade: ");
        scanf("%s", nome);

        if (strcmp(nome, "f") == 0) {
            dequeue(&queue);
        }
        if (strcmp(nome, "x") == 0) {
            break;
        }

        scanf("%d", &prioridade);
        getchar();

        if (prioridade > 2){printf ("ERRO! \n"); break;}

        enqueue(&queue, nome, prioridade);
        printPriorityQueue(&queue);

        if (ind == capacidade) { 
            printf("Se quiser liberar alguém pressione 'f', se quiser encerrar pressione 'x': ");
            scanf("%s", nome);
            if (strcmp(nome, "f") == 0) {
            dequeue(&queue);
            }
            else if (strcmp(nome, "x") == 0) {
            break;
            }
            else { printf("\nDesculpe, não será possivel atender mais ninguém.\n");break;}
        }

        for(int j = 0; j< capacidade - ind; j++){
                printf("Paciente: ???, Prioridade: ?, Tempo de espera: ?? min \n");
        } 

        ind++;
    }
    
    return 0;
}

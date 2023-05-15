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

void enqueue(PriorityQueue* queue, char* nome, int priority) {
    
        if (queue->size == queue->capacity) {
        printf("Não conseguimos atender mais ninguém\n");
        return;
        }
    
    QueueItem item;
    strcpy(item.nome, nome);
    item.prioridade = priority;

    int i = queue->size - 1;
    while (i >= 0 && queue->items[i].prioridade < priority) {
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
    
    if (queue->size == 0) {
        printf("Vazia!\n");
        return;
    }
    
    for (int i = 0; i < queue->size; i++) {
        printf("nome: %s, Prioridade: %d, Tempo de espera: %d min \n", queue->items[i].nome, queue->items[i].prioridade, i * 30 );
    }
}

int main() {
    int capacidade, prioridade;
    char nome[100];
    
    printf("Insira a quantidade de fichas que irão ser dadas na recepção: ");
    scanf("%d", &capacidade);
    getchar();  // Consume the newline character
    
    PriorityQueue queue;
    initializePriorityQueue(&queue, capacidade);
    
     while (1) {
        printf("insira o nome do paciente e seu nível de prioridade (ou pressione x para sair do menu): ");
        scanf("%s", nome);
        if (strcmp(nome, "x") == 0) {
            break;
        }
        scanf("%d", &prioridade);
        getchar();  // Consume the newline character

        dequeue(&queue);
        enqueue(&queue, nome, prioridade);
        printPriorityQueue(&queue); 
    }
    
    printf("\nEsvaziando \n");
    while (queue.size > 0) {
        char* nome = dequeue(&queue);
        printf("%s\n", nome);
        printPriorityQueue(&queue);
    }
    
    return 0;
}

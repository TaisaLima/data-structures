#include <stdio.h>
#include <string.h>

#define MAX_CAPACITY 100

typedef struct {
    char name[100];
    int priority;
} QueueItem;

typedef struct {
    QueueItem items[MAX_CAPACITY];
    int capacity;
    int size;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue* queue, int capacity) {
    queue->capacity = capacity;
    queue->size = 0;
}

void enqueue(PriorityQueue* queue, char* name, int priority) {
    if (queue->size == queue->capacity) {
        printf("Não conseguimos atender mais ninguém\n");
        return;
    }
    
    QueueItem item;
    strcpy(item.name, name);
    item.priority = priority;
    
    int i = queue->size - 1;
    while (i >= 0 && queue->items[i].priority < priority) {
        queue->items[i + 1] = queue->items[i];
        i--;
    }
    
    queue->items[i + 1] = item;
    queue->size++;
}

char* dequeue(PriorityQueue* queue) {
    if (queue->size == 0) {
        printf("Priority queue is empty\n");
        return NULL;
    }
    
    char* name = queue->items[queue->size - 1].name;
    queue->size--;
    return name;
}

void printPriorityQueue(PriorityQueue* queue) {
    printf("Priority Queue:\n");
    printf("---------------\n");
    
    if (queue->size == 0) {
        printf("Empty\n");
        return;
    }
    
    for (int i = 0; i < queue->size; i++) {
        printf("Name: %s, Priority: %d\n", queue->items[i].name, queue->items[i].priority);
    }
}

int main() {
    int capacity;
    printf("Enter the capacity of the priority queue: ");
    scanf("%d", &capacity);
    getchar();  // Consume the newline character
    
    PriorityQueue queue;
    initializePriorityQueue(&queue, capacity);
    
    char name[100];
    int priority;
    
    while (1) {
        printf("Enter a name and priority (or 'quit' to exit): ");
        scanf("%s", name);
        if (strcmp(name, "quit") == 0) {
            break;
        }
        scanf("%d", &priority);
        getchar();  // Consume the newline character
        
        enqueue(&queue, name, priority);
        printPriorityQueue(&queue);
    }
    
    printf("\nDequeuing names in priority order:\n");
    while (queue.size > 0) {
        char* name = dequeue(&queue);
        printf("%s\n", name);
        printPriorityQueue(&queue);
    }
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

// Função para criar um novo nó
struct Node* create_node(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Função para empilhar um elemento
void push(struct Node** top, int data) {
    struct Node* node = create_node(data);
    node->next = *top;
    *top = node;
}
long long pop(Stack *s) {

    if (s->top == NULL) {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
    long long c = s->top->data;
    Node *temp = s->top;
    s->top = s->top->next;
    free(temp);
    return c;
}


// Função para encontrar o maior número possível
long long find_max_num(char* num, int n, int m, int k, int w) {
    struct Node* int_stack = NULL; // Pilha para os dígitos da parte inteira
    struct Node* frac_stack = NULL; // Pilha para os dígitos da parte fracionária
    
    // Preenchendo a pilha dos dígitos da parte inteira
    int i = 0;
    while (num[i] != '.' && i < n) {
        push(&int_stack, num[i] - '0');
        i++;
    }
    
    // Preenchendo a pilha dos dígitos da parte fracionária
    i++;
    while (i < n + m + 1) {
        push(&frac_stack, num[i] - '0');
        i++;
    }
    
    // Removendo k dígitos da parte inteira
    while (k > 0 && int_stack != NULL) {
        pop(&int_stack);
        k--;
    }
    
    // Removendo w dígitos da parte fracionária
    while (w > 0 && frac_stack != NULL) {
        pop(&frac_stack);
        w--;
    }
    
    // Construindo o maior número possível
    long long max_num = 0;
    while (int_stack != NULL) {
        max_num = max_num * 10 + stack_top(int_stack);
        pop(&int_stack);
    }
    max_num *= pow(10, m);
    while (frac_stack != NULL) {
        max_num += stack_top(frac_stack) * pow(10, m - frac_stack->data);
        pop(&frac_stack);
    }
    
    return max_num;
}

int main() {
    char num[1000001];
    int n, m, k, w;
    printf("Digite o número: ");
    scanf("%s", num);
    printf("Digite o número de dígitos na parte inteira: ");
    scanf("%d", &n);
    printf("Digite o número de dígitos na parte fracionária: ");
    scanf("%d", &m);
    printf("Digite o número de dígitos a serem removidos da parte inteira: ");
    scanf("%d", &k);
    printf("Digite o número de dígitos a serem removidos da parte fracionária: ");
    scanf("%d", &w);
    long long max_num = find_max_num(num, n, m, k, w);
    printf("O maior número possível é: %lld\n", max_num);
    return 0;
}

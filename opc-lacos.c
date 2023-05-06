#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void push(Stack *s, char c) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = c;
    new_node->next = s->top;
    s->top = new_node;
}

char pop(Stack *s) {
    if (s->top == NULL) {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
    char c = s->top->data;
    Node *temp = s->top;
    s->top = s->top->next;
    free(temp);
    return c;
}

char peek(Stack *s) {
    if (s->top == NULL) {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
    return s->top->data;
}

int is_empty(Stack *s) {
    return (s->top == NULL);
}

  void display1(Stack *s)
    {
         struct Node *p;
         p= s->top;
         while(p!=NULL)
         {
             printf("%d",(p->data)-48);
             p=p->next;
         }
    }

  void display2(Stack *s)
    {
         struct Node *p;
         p= s->top;
         
         printf(".");
         while(p!=NULL)
         {
             printf("%d",(p->data)-48);
             p=p->next;
         }
         printf("\n");
    }

int main() {
    char n_str[50];
    int m, k, w, len_int, len_frac, i, j;
    Stack int_stack, frac_stack;
    int_stack.top = NULL;
    frac_stack.top = NULL;
    scanf("%s %d %d", n_str, &k, &w);

    // Separa a parte inteira da parte fracionária
    char *int_part = strtok(n_str, ".");
    char *frac_part = strtok(NULL, ".");
    len_int = strlen(int_part);
    len_frac = strlen(frac_part);

    // Insere os dígitos da parte inteira na pilha
    for (i = 0; i < len_int; i++) {
        push(&int_stack, int_part[i]);
    }
    // Insere os dígitos da parte fracionária na pilha
    for (i = 0; i < len_frac; i++) {
        push(&frac_stack, frac_part[i]);
    }

    // Remove k dígitos da parte inteira
    for (i = 0; i < k; i++) {
        Node *prev = NULL;
        Node *curr = int_stack.top;
        while (curr != NULL && curr->next != NULL) {
            if (curr->data < curr->next->data) {
                if (prev == NULL) {
                    int_stack.top = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
                break; 
            }
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL || curr->next == NULL) {
            if (prev == NULL) {
                int_stack.top = NULL;
            } else {
                prev->next = NULL;
            }
            free(curr);
        }
    }
    // Remove w dígitos da parte fracionária
       for (i = 0; i < k; i++) {
        Node *prev = NULL;
        Node *curr = frac_stack.top;
        while (curr != NULL && curr->next != NULL) {
            if (curr->data < curr->next->data) {
                if (prev == NULL) {
                    frac_stack.top = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
                break; 
            }
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL || curr->next == NULL) {
            if (prev == NULL) {
                frac_stack.top = NULL;
            } else {
                prev->next = NULL;
            }
            free(curr);
        }
    }

    

    display1 (&int_stack);
    display2 (&frac_stack);


    return 0;
}

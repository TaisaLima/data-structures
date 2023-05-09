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
        exit(1);}
    char c = s->top->data;
    Node *temp = s->top;
    s->top = s->top->next;
    free(temp);
    return c;
}

//a funcao q printa a parte inteira
 void display1(Stack *s, int w)
    {
        struct Node *p;
        p= s->top;
        int i=0;
        int array[1002];
        while(p!=NULL && i < w){
            array[i]=((p->data)-48);
            p=p->next;
            i++;
        }

        for (i;i>0;i--) {printf("%d",array[i-1]);}
    }

//a funcao q printa a parte fracionaria (são diferentes por conta da questao da virgula e da quebra de linha)
  void display2(Stack *s, int k)
    {
        struct Node *p;
        p= s->top;
        int i=0;
        int array[1002];
        printf(".");
         while(p!=NULL){
             array[i]=((p->data)-48);
             p=p->next;
             i++;
         }

        for (i;i>0;i--){printf("%d",array[i-1]);}
        printf("\n");
    }
 
int main() {

    char num[50];
    int m, k, w, len_int, len_frac, i, j;
    Stack int_stack, frac_stack, aux;
    int_stack.top = NULL;
    frac_stack.top = NULL;
    aux.top=NULL;

    printf("Insira seu float:  "); scanf ("%s" , num);
    printf("\nQuantos digitos deseja cortar de cada lado?   "); scanf ("%d %d", &w, &k);

    // Separa a parte inteira da parte fracionária
    char *int_part = strtok(num, ".");
    char *frac_part = strtok(NULL, ".");
    len_int = strlen(int_part);
    len_frac = strlen(frac_part);
    int erased = 0;

    // Insere os dígitos da parte inteira na pilha
    for (j = 0; j < len_int; j++) {
        while(int_stack.top != NULL && erased < w && int_stack.top->data  < int_part[j]) {
            pop(&int_stack);
            erased++;
        }
        push(&int_stack, int_part[j]); 
    }
    // Insere os dígitos da parte fracionária na pilha
    erased = 0;
    for (m = 0; m < len_frac; m++) {
        while(frac_stack.top != NULL && erased < k && frac_stack.top->data  < frac_part[m]) {
            pop(&frac_stack);
            erased++;
        }
        push(&frac_stack, frac_part[m]);
    }
    //tratamento de erro
    if (j <w || m <k) {printf("\nERRO: caso de teste invalido\n"); return 0;}

    //mostrar resultado na tela  
    if ( j == w) printf("0");
    else display1 (&int_stack, len_int - w);

    if (k==m) printf("\n");
    else display2 (&frac_stack, len_frac - k);

    return 0;
} 

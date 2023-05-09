#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void PRINTARRAY(char array[], int length){for(int i = 0; i < length; i++){printf("%d ", array[i]);}}
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

 void display1(Stack *s)
    {
        struct Node *p;
        p= s->top;

        int i=0;
        int array[1002];
        while(p!=NULL)
        {
            array[i]=((p->data)-48);
            p=p->next;
            i++;
        }

        for (i;i>0;i--)
        {
            printf("%d",array[i-1]);
            
        }

    }

  void display2(Stack *s)
    {
        struct Node *p;
        p= s->top;
        int i=0;
        int array[1002];
         
         printf(".");
         while(p!=NULL)
         {
             array[i]=((p->data)-48);
             p=p->next;
             i++;
         }
         
         for (i;i>0;i--)
         {
             printf("%d",array[i-1]);
             
         }
        printf("\n");

    }

void swap(char *xp, char *yp)
{
    char temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
int thelastofus(char arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);

    return arr[0];
}

int main() {

    char num[50];
    int m, k, w, len_int, len_frac, i, j;
    Stack int_stack, frac_stack, aux;
    int_stack.top = NULL;
    frac_stack.top = NULL;
    aux.top=NULL;



    printf("Insira seu float:  ");
    scanf ("%s" , num);
    printf("\nQuantos digitos deseja cortar de cada lado?   ");
    scanf ("%d %d", &w, &k);


    // Separa a parte inteira da parte fracionária
    char *int_part = strtok(num, ".");
    char *frac_part = strtok(NULL, ".");
    len_int = strlen(int_part);
    len_frac = strlen(frac_part);

    // Insere os dígitos da parte inteira na pilha
    for (j = 0; j < len_int; j++) {
        push(&int_stack, int_part[j]); 
    }
    // Insere os dígitos da parte fracionária na pilha
    for (m = 0; m < len_frac; m++) {
        push(&frac_stack, frac_part[m]);
    }

    //tratamento de erro
    if (j <w || m <k) {printf("\nERRO: caso de teste invalido\n"); return 0;}
    

    // Remove w dígitos da parte inteira
        for (i = 0; i < w; i++) {
            Node *prev = NULL;
            Node *curr = int_stack.top;
            while (curr != NULL && curr->next != NULL) {
                if (curr->data < curr->next->data) {
                    if ((prev == NULL)) {
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
    // Remove k dígitos da parte fracionária
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




    //mostrar resultado na tela
    if ( j == w) printf("0");
    else display1 (&int_stack);

    if (k==m) printf("\n");
    else display2 (&frac_stack);


    

    return 0;
} 






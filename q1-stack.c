#include <stdio.h>
#include <math.h>
#include <stdlib.h>


typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;
    
void push(Stack *s, int x)
{
    struct Node *t;
    t=(struct Node*)malloc(sizeof(struct Node));
    
    if(t==NULL) return 0;
    else{
        t->data=x;
        t->next=top;
        top=t;
    }
    
}

int pop(Stack *s)
{
        struct Node *t;
        int x=-1;
        
        if(top==NULL)
        printf("Stack is Empty\n");
        else{
            
            t=top;
            top=top->next;
            x=t->data;
            free(t);
        }
        return x;
}

    
  void mostre(Stack *s)
    {
         struct Node *p;
         p= s->top;
         while(p!=NULL)
         {
             printf("%d ",p->data);
             p=p->next;
         }
         printf("\n");
    }

    void where_to_cut (int intpart, int w){

        int cort [w];
                      
        int soma = 0;
        for (int i=0;intpart > 0;i++){
    
        soma =  intpart % 10;
        intpart = intpart /10;
        //if (soma >  Node->top)

        }


    }
    
    int main(){

        double  num;
        int w, k,i;
        Stack int_stack, frac_stack;

        int_stack.top = NULL;
        frac_stack.top = NULL;

        
        printf("Insira seu float:  ");
        scanf ("%lf" , &num);
        printf("\nQuantos digitos deseja cortar de cada lado?   ");
        scanf ("%d %d", &w, &k);


        //divide o numero em duas variaveis inteiras
        int intpart = (int)num;
        int decpart = (num - intpart)*1000;

        //coloca digito por digito da parte inteira na pilha
        int soma = 0, j=0;
        while(intpart > 0){
        soma =  intpart % 10;
        intpart = intpart /10;
        push (&int_stack, soma);
        j++;
        }

        //coloca digito por digito da parte fracionaria na pilha
        int somaf = 0, m=0;
        while(decpart > 0){
        somaf =  decpart % 10;
        decpart = decpart /10;
        push (&frac_stack,somaf);
        m++;
        }

        //tratamento de erro
        if (j>w || m>k) {printf("\nERRO: caso de teste invalido\n"); return 0;}

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

        mostre(&int_stack);
        return 0;

        
    }
    
    
    
    
    


    

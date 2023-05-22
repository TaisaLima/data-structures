 #include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>
#define MAX 100

typedef struct {
    char nome[MAX];
    int prioridade;
    int dia;
} QueueItem;

typedef struct {
    QueueItem items[MAX];
    int capacity;
    int size;
} PriorityQueue;

void inicializarFila(PriorityQueue* queue, int capacity) {
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

void printarFila(PriorityQueue* queue) {
    printf("Ordem de chamada: \n");
    printf("---------------\n");
    printf("\n\n");
    
    if (queue->size == 0) {
        printf("Vazia!\n");
        return;
    }
    
    for (int i = 0; i < queue->size; i++) {
        printf("Paciente: %s, Prioridade: %d, Tempo de espera: %d min \n", queue->items[i].nome, queue->items[i].prioridade, i * 30 );
    }
}


void diaSemana(){

    printf("1) Segunda\n");
    printf("2) Terça\n");
    printf("3) Quarta\n");
    printf("4) Quinta\n");
    printf("5) Sexta\n");
    printf("6) Sábado\n");
    printf("7) Domingo\n\n");
    printf("Digite o número correspondente:  ");
}
 
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int disponibilidade(PriorityQueue* queue){

    if (queue->size == queue->capacity) {
    return 0;
    }

    return 1;
}

void cadastro(PriorityQueue* segunda, int prior ){
    printf("okokokokokook lalalalalala \n");
    delay(100000);
}

int agendamento(PriorityQueue* segunda, PriorityQueue* terca, PriorityQueue* quarta, PriorityQueue* quinta, PriorityQueue* sexta,  PriorityQueue* sabado, PriorityQueue* domingo){

    int data, vagas;char resposta;

    system("clear");    
    printf("--------------  MENU DE AGENDAMENTO  -------------- \n\n");
    printf("Para qual dia da semana deseja agendar? \n\n");
    diaSemana();
    scanf("%d", &data);
    printf ("\nAguarde enquanto checamos se há vagas disponiveis na data\n\n");    
    delay(1000);
    
    switch (data){
        case 1: vagas =disponibilidade(segunda);
        case 2: vagas =disponibilidade(terca);
        case 3: vagas =disponibilidade(quarta);  
        case 4: vagas =disponibilidade(quinta); 
        case 5: vagas =disponibilidade(sexta);
        case 6: vagas =disponibilidade(sabado);    
        case 7: vagas =disponibilidade(domingo);
    }

    if (vagas == 0) {
        printf ("Não há mais vaga para esse dia, gostaria de marcar em outra data?('S' ou 'N') "); 
        scanf (" %c", &resposta);
        if (resposta == ('S' || 's')) return agendamento( segunda, terca, quarta, quinta, sexta, sabado, domingo);
        if (resposta == ('N' || 'n')) {printf("Sentimos muito pelo transtorno. Retornaremos ao menu principal."); delay(1000); return 0;}
    }


    switch (data){
        case 1: cadastro(segunda, 3);
        case 2: cadastro(terca, 3);
        case 3: cadastro(quarta, 3);  
        case 4: cadastro(quinta, 3); 
        case 5: cadastro(sexta, 3);
        case 6: cadastro(sabado, 3);    
        case 7: cadastro(domingo, 3);
    }

    return 0;

}

void menuPrincipal(PriorityQueue* segunda, PriorityQueue* terca, PriorityQueue* quarta, PriorityQueue* quinta, PriorityQueue* sexta,  PriorityQueue* sabado, PriorityQueue* domingo){

    char nome[100];
    int capacidade, escolha=0,prioridade, ind=1;
    system("clear");
    printf("\n\nBem-vindo ao hospital. Em quê podemos ajudar? \n\n");
    printf("1) Fazer um AGENDAMENTO;");
    printf("\n2) Inserir paciente na fila de EMERGENCIA");
    printf("\n3) Confirmar DESISTÊNCIA");
    printf("\n4) Consultar FILA DO DIA\n");
    printf("5) SAIR\n\n");
    printf("Digite o número correspondente ao seu problema:  ");

       scanf("%d", &escolha);

    switch(escolha){

        case 1:
            agendamento( segunda, terca, quarta, quinta, sexta, sabado, domingo);
        case 2:
            printf("\n\n\n");
            case 3:
            printf("\n\n\n");
            case 4:
            printf("\n\n\n");
            case 5: return;
     }

}

int main() {

    PriorityQueue segunda, terca, quarta, quinta, sexta, sabado, domingo;
    
    inicializarFila(&segunda, 72);
    inicializarFila(&terca, 72);
    inicializarFila(&quarta, 72);
    inicializarFila(&quinta, 72);
    inicializarFila(&sexta, 72);
    inicializarFila(&sabado, 72);
    inicializarFila(&domingo, 72);


    menuPrincipal(&segunda, &terca, &quarta, &quinta, &sexta, &sabado, &domingo); 
 


  
    return 0;
}

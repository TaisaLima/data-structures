#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>
#define MAX 100
int pacido=0,pacisa=0,pacisexta=0,paciqui=0, paciqua=0, pacite=0, pacise=0;

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

void enqueue(PriorityQueue* segunda, PriorityQueue* terca, PriorityQueue* quarta, PriorityQueue* quinta, PriorityQueue* sexta,  PriorityQueue* sabado, PriorityQueue* domingo, char* nome, int prioridade, int data) {
   
   PriorityQueue* queue; int rodizio;
   
    if (data == 1) { queue = segunda;   pacise++;   rodizio = pacise;} 
    if (data == 2) { queue = terca;     pacite++;   rodizio= pacite;} 
    if (data == 3) { queue = quarta;    paciqua++;  rodizio= paciqua;} 
    if (data == 4) { queue = quinta;    paciqui++;  rodizio= paciqui;} 
    if (data == 5) { queue = sexta;     pacisexta++;rodizio= pacisexta;} 
    if (data == 6) { queue = sabado;    pacisa++;   rodizio= pacisa;} 
    if (data == 7) { queue = domingo;   pacido++;   rodizio= pacido;} 

    QueueItem item;
    strcpy(item.nome, nome);
    item.prioridade = prioridade;
    int i = queue->size - 1;

    while ((i >= 0 && queue->items[i].prioridade > prioridade)) {
        queue->items[i + 1] = queue->items[i];
        i--;
    }
   
    queue->items[i + 1] = item;
    queue->size++;
   
    return;

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

void printarFila(PriorityQueue* queue, int quant) {
    printf("Ordem de chamada: \n");
    printf("---------------\n\n");

    if (quant ==0 ) printf("\nFila vazia!\n");

    for (int i = 0; i < quant; i++) {
        printf("Paciente: %s, Prioridade: %d, Tempo de espera: %d min \n", queue->items[i].nome, queue->items[i].prioridade, i * 30 );
    }
}

void diaSemana(){
    printf("\n1) Segunda\n");
    printf("2) Terça\n");
    printf("3) Quarta\n");
    printf("4) Quinta\n");
    printf("5) Sexta\n");
    printf("6) Sábado\n");
    printf("7) Domingo\n\n");
    printf("Digite o número correspondente:  ");
}
 
int disponibilidade(PriorityQueue* segunda, PriorityQueue* terca, PriorityQueue* quarta, PriorityQueue* quinta, PriorityQueue* sexta,  PriorityQueue* sabado, PriorityQueue* domingo, int data){

    if (data == 1) {if (segunda->size == segunda->capacity) return 0;} 
    if (data == 2) {if (terca->size == terca->capacity) return 0;}
    if (data == 3) {if (quarta->size == quarta->capacity) return 0;}  
    if (data == 4) {if (quinta->size == quinta->capacity) return 0;}
    if (data == 5) {if (sexta->size == sexta->capacity) return 0;}
    if (data == 6) {if (sabado->size == sabado->capacity) return 0;}
    if (data == 7) {if (domingo ->size == domingo->capacity) return 0;}    

    return 1;
}

void cadastro(PriorityQueue* segunda, PriorityQueue* terca, PriorityQueue* quarta, PriorityQueue* quinta, PriorityQueue* sexta,  PriorityQueue* sabado, PriorityQueue* domingo, int data, int ag){
   
    char nome[100]; int prioridade, ind=1;
    printf("insira o nome do paciente:  ");
    scanf("%s", nome);
    if (strcmp(nome, "x") == 0) return;

    if (ag != 3){
    printf("insira a idade: ");
    scanf("%d", &prioridade);
    
        if ((prioridade <= 5) || (prioridade >= 80)) prioridade = 0;
        if ((prioridade > 5) && (prioridade <= 16)) prioridade = 1;
        if ((prioridade < 80) && (prioridade > 16)) prioridade = 2;
        
    getchar();
    }
    
    if (ag == 3) prioridade = 3;
    if (prioridade > 3){printf ("ERRO! \n"); return;}

    enqueue(segunda, terca, quarta, quinta, sexta, sabado, domingo, nome, prioridade, data);

}

int main(){

    PriorityQueue segunda, terca, quarta, quinta, sexta, sabado, domingo;
    int capacidade, escolha=0,prioridade, ind=1, opc=0, vagas=2;
    char nome[100];
    char resposta;
   
    //criar as filas com 72 lugares pois é estimado que o hospital funcione 24 horas e atenda cada paciente em 20 min
    inicializarFila(&segunda, 72); inicializarFila(&terca, 72); inicializarFila(&quarta, 72); inicializarFila(&quinta, 72);
    inicializarFila(&sexta, 72);inicializarFila(&sabado, 72); inicializarFila(&domingo, 72);

    // loop para sempre retornar ao menu principal ao término de uma operação
    while (1){
       
    system("clear");
    printf("\n\nBem-vindo ao hospital. Em quê podemos ajudar? \n\n");
    printf("1) Fazer um AGENDAMENTO;");
    printf("\n2) Inserir paciente na fila de EMERGENCIA");
    printf("\n3) Confirmar DESISTÊNCIA");
    printf("\n4) Consultar FILA DO DIA\n");
    printf("5) SAIR\n\n");
    printf("Digite o número correspondente ao seu problema:  ");

    
    scanf("%d", &escolha); 
    if ((opc > 1) || (opc > 5)) {printf("Erro! \n"); return 0;}

    //parte funcional do menu
    switch(escolha){
            //agendamento
            case 1: 
            
                printf("\n\n--------------  MENU DE AGENDAMENTO  -------------- \n\n");
                printf("Para qual dia da semana deseja agendar? \n\n");
                //funçao utilizada para printar dias da semana 
                diaSemana();
                scanf("%d", &opc);getchar();
                
                //tratamento de erro 
                if ((opc != 1)&(opc != 2)&(opc != 3)&(opc != 4)&(opc != 5)&(opc != 6)&(opc != 7)) break;

                printf ("\nAguarde enquanto checamos se há vagas disponiveis na data\n\n");    
                vagas = disponibilidade(&segunda, &terca, &quarta, &quinta, &sexta, &sabado, &domingo, opc);
               
                    if (vagas == 0) {
                        printf ("Não há mais vaga para esse dia, gostaria de outra data?('S' ou 'N') ");
                        scanf (" %c", &resposta);
                        if (resposta == ('S' || 's')) break;
                        if (resposta == ('N' || 'n')) {printf("Sentimos muito pelo transtorno. Retornaremos ao menu principal."); getchar();break;}
                    }

                cadastro(&segunda, &terca, &quarta, &quinta, &sexta, &sabado, &domingo,opc, 3);

            break;

            case 2:

                printf("\n\n--------------  MENU DA EMERGENCIA  -------------- \n\n");
                printf("Para qual dia da semana deseja agendar? \n\n");
                diaSemana();
                
                scanf ("%d", &opc);getchar();

                if ((opc != 1)&&(opc != 2)&&(opc != 3)&&(opc != 4)&&(opc != 5)&&(opc != 6)&&(opc != 7)) break;

                //verifica se é possivel fazer a opraçao no dia escolhido
                printf ("\nAguarde enquanto checamos se há vagas disponiveis na data\n\n");    
                vagas = disponibilidade(&segunda, &terca, &quarta, &quinta, &sexta, &sabado, &domingo, opc);
                //tratamento de erro
                if (vagas == 0) {
                    printf ("Não há mais vaga para esse dia, gostaria de outra data?('S' ou 'N') ");
                    scanf (" %c", &resposta);
                    if (resposta == ('S' || 's')) break;
                    if (resposta == ('N' || 'n')) {printf("Sentimos muito pelo transtorno. Retornaremos ao menu principal.");getchar(); break;}
                }
                
                cadastro(&segunda, &terca, &quarta, &quinta, &sexta, &sabado, &domingo,opc, 0);
                        
            break;
            
            case 3:
            
                printf("\n\n--------------  MENU DA DESISTENCIA -------------- \n\n");
                printf("Qual a data de desistência? \n\n");
                diaSemana();
                scanf ("%d", &opc);getchar();
                
                if ((opc != 1)&&(opc != 2)&&(opc != 3)&&(opc != 4)&&(opc != 5)&&(opc != 6)&&(opc != 7)) break;

                if (opc == 1) {dequeue(&segunda);pacise--;}
                if (opc == 2) {dequeue(&terca);pacite--;}
                if (opc == 3) {dequeue(&quarta);paciqua--;}  
                if (opc == 4) {dequeue(&quinta);paciqui--;}
                if (opc == 5) {dequeue(&sexta);pacisexta--;}
                if (opc == 6) {dequeue(&sabado);pacisa--;}    
                if (opc == 7) {dequeue(&domingo);pacido--;}
                
            break;
        
            case 4:

                diaSemana();
                scanf ("%d", &opc);getchar();
                if ((opc != 1)&&(opc != 2)&&(opc != 3)&&(opc != 4)&&(opc != 5)&&(opc != 6)&&(opc != 7)) break;
    

                if (opc == 1) printarFila(&segunda , pacise);
                if (opc == 2) printarFila(&terca , pacite);
                if (opc == 3) printarFila(&quarta , paciqua);  
                if (opc == 4) printarFila(&quinta , paciqui);
                if (opc == 5) printarFila(&sexta , pacisexta);
                if (opc == 6) printarFila(&sabado , pacisa);    
                if (opc == 7) printarFila(&domingo , pacido);
                    
                    
                printf("\nPressione enter para retornar ao menu principal\n");
                getchar();
                    
                break;

        
            case 5: 
            return 0;

        }
    }
    return 0;
}

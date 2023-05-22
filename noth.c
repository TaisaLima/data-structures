#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iso646.h>
#include <time.h>

#define MAX_SIZE 100

int senha = 1;
int flag = 0;
int tam = 50;

typedef struct {
    char nome[50];
    int prioridade; 
    int idade;
    int senha;
} Paciente;

typedef struct {
    Paciente filaEspera[MAX_SIZE];
    int inicio;
    int fim;
    //int tamanho;
} Fila;


Paciente PacienteNovo(){
    Paciente novoPaciente;

    printf("Digite o nome do paciente: ");
    fgets(novoPaciente.nome, 50, stdin);
    novoPaciente.nome[strlen(novoPaciente.nome) - 1] = '\0';
    
    printf("Digite a idade do paciente: ");
    scanf("%d", &novoPaciente.idade);
    novoPaciente.senha = senha;
    senha++;

    
    if (novoPaciente.idade < 5 or novoPaciente.idade > 80) novoPaciente.prioridade = 2;
    else if (novoPaciente.idade < 16 or novoPaciente.idade > 60) novoPaciente.prioridade = 1;
    else novoPaciente.prioridade = 0;
    
    return novoPaciente;
}

int cheia(Fila* fila) {
    //return (fila->tamanho == MAX_SIZE);
}

void inicializar(Fila* fila) {
    fila->inicio = -1;
    fila->fim = -1;
}

int PrioridadeReal(int value){
    return (not value) ? 2 : (value == 1) ? 1 : 0;
}

bool isEmpty(Fila list){
    if(flag == 0){
        return 1;
    }
    return (list.inicio > list.fim);
}

void enqueue(Fila *fila, Paciente pessoa) {
    if (fila->fim == tam-1) {
        printf("A fila esta cheia!\n");
        return;
    }

    if (fila->inicio == -1 and fila->fim == -1) {
        fila->inicio = 0;
        fila->fim = 0;
        //fila->tamanho = 1;
        fila->filaEspera[fila->fim] = pessoa;
    } else {
        int i, j;
        for (i = fila->inicio; i <= fila->fim; i++) {
            if (pessoa.prioridade < fila->filaEspera[i].prioridade) {
                for (j = fila->fim + 1; j > i; j--) {
                    fila->filaEspera[j] = fila->filaEspera[j - 1];
                }
                fila->filaEspera[i] = pessoa;
                fila->fim++;
                //fila->tamanho++;
                break;
            }
        }
        if (i > fila->fim) {
            fila->fim++;
            //fila->tamanho++;
            fila->filaEspera[fila->fim] = pessoa;
        }
    }

    flag = 1;
}

Paciente dequeue(Fila *fila) {
    if (fila->inicio == -1) {
        Paciente empty = {-1, -1};
        return empty;
    }
    Paciente patient = fila->filaEspera[fila->inicio];
    fila->inicio += (fila->inicio > fila->fim) ? 0 : 1;

    return patient;
}

void exibirFila(Fila fila, int j, int i){
    if(i > fila.fim) return;
    printf("Lugar na fila: %d || Nome: %s || Idade: %d || Prioridade: %d || Senha: %d\n", j, fila.filaEspera[i].nome, fila.filaEspera[i].idade, PrioridadeReal(fila.filaEspera[i].prioridade), fila.filaEspera[i].senha);
    exibirFila(fila, j+1, i+1);
}

Fila fazerRodizio(Fila Hospital)
{
    Fila aux;
    //inicializar(&aux);
    aux.inicio = Hospital.inicio;
    aux.fim = Hospital.inicio;

    for (int i = Hospital.inicio; i <= Hospital.fim; i++){
        Hospital.filaEspera[i].prioridade = (Hospital.filaEspera[i].prioridade + 1) % 3;
    }

    int i = Hospital.inicio;
    while(aux.fim != Hospital.fim)
    {
        enqueue(&aux, Hospital.filaEspera[i]);
        i++;
    }

    return aux;
}

int main() {
    Fila Hospital;
    inicializar(&Hospital);

    srand(time(NULL));
    int cont = 0, rodizio = 1, escolha;
    double tempoGasto = 0;

    printf("Digite quantas pessoas serao antedidas no dia de hoje: ");

    while(1){
        printf("Opcoes:\n\n(0) - Sair\n(1) - Inserir pessoa na fila\n(2) - Atender\n(3) - Ver fila atual\n(4) - Ver tempo gasto\n\n");
        printf("\nEscolha um numero: ");    
        if(rodizio % 5 == 0){
            rodizio = 0;
            for (int i = Hospital.inicio; i <= Hospital.fim; i++){
            Hospital.filaEspera[i].prioridade = (Hospital.filaEspera[i].prioridade + 1) % 3;
            }
            //Hospital = fazerRodizio(Hospital);
            }
        
        scanf("%d", &escolha);
        getchar();
        switch(escolha){
            case 0:
                exit(0);
                break;
            
            case 1:
                if(cont < tam){
                    enqueue(&Hospital, PacienteNovo());
                }
                else{
                    printf("O numero maximo de antendimentos por dia foi atingido!\n");
                    exit(0);
                }

            break;

            case 2:
                if(!isEmpty(Hospital)){
                dequeue(&Hospital);
                rodizio++;
                tempoGasto += ((rand() % 20)) + 20;
                printf("Pessoa atendida.\n");
                getchar();
                } 
                else{
                printf("A fila esta vazia!\n");
                getchar();
                }
            break;

            case 3:
            if(!isEmpty(Hospital))
                exibirFila(Hospital, 1, Hospital.inicio);
            else printf("A fila esta vazia!\n");    
            getchar();
            break;

            case 4:
            printf("\nTempo gasto das consultas ate agora: %.0lf minutos/%.1lf hora(s)\n", tempoGasto, tempoGasto/60);
            getchar();
            break;
        }
    }
    return 0;
}

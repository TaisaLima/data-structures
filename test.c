#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEVADORES 15
#define NUM_CORREDORES 3
#define TOTAL_ANDARES 300

typedef struct Elevador{
 char nome;
 int andarInit;
 int corredorInit;
 int andar;
 int corredor;
 int estado;
 int andarDestino;
 int corredorDestino;
 char movimento;
} Elevador;

Elevador elevadores[NUM_ELEVADORES];
Elevador listaPrioridades[NUM_ELEVADORES];
Elevador listaEspera[10];

char predio[TOTAL_ANDARES][NUM_CORREDORES];

int ANDAR;
int CORREDOR;
int countPrior = 0;

void imprimePredio(){
 for(int i=TOTAL_ANDARES-1; i>=0; i--){
 printf("%d ", i);
 for(int j=0; j<3; j++){
 printf("%c ", predio[i][j]);
 }
 printf("\n");
 }
}

void inicializarPredio(){
 for(int i=0; i<TOTAL_ANDARES; i++){
 for(int j=0; j<NUM_CORREDORES; j++){
 predio[i][j]='-';
 }
 }
 for(int replace=0; replace<NUM_ELEVADORES; replace++){
 predio[elevadores[replace].andar][elevadores[replace].corredor]=elevadores[replace].nome;
 }
 imprimePredio();
}

void atualizaPredio(){
 for(int i=0; i<TOTAL_ANDARES; i++){
 for(int j=0; j<NUM_CORREDORES; j++){
 predio[i][j]='-';
 }
 }
 for(int replace=0; replace<NUM_ELEVADORES; replace++){
 predio[elevadores[replace].andar][elevadores[replace].corredor]=elevadores[replace].nome;
 }
}

void inicializarElevadores() {
 int count = 0;
 for (int i = 0; i < NUM_ELEVADORES; i++) {
 if(i%3==1){
 count=10;
 }
 else if(i%3==2){
 count=20;
 }
 else{
 count = 0;
 }
 elevadores[i].nome = 65+i;
 elevadores[i].andarInit = (i % 5 * 60)+count;
 elevadores[i].corredorInit = i % 3;
 elevadores[i].andar = (i % 5 * 60)+count;
 elevadores[i].corredor = i % 3;
 elevadores[i].estado = 0;
 }
}

void substituiElevadores(){
 for(int i=0; i<NUM_ELEVADORES; i++){
 for(int j=0; j<NUM_ELEVADORES && listaPrioridades[j].nome!=0; j++){
 if(elevadores[i].nome==listaPrioridades[j].nome){
 elevadores[i].andar=listaPrioridades[j].andar;
 elevadores[i].corredor=listaPrioridades[j].corredor;
 elevadores[i].estado=listaPrioridades[j].estado;
 elevadores[i].andarDestino=listaPrioridades[j].andarDestino;
 elevadores[i].corredorDestino=listaPrioridades[j].corredorDestino;
 break;
 }
 }
 }
}

int countEspera = 0;

void deslocamento(int andarAtual, int corredorAtual, int lado, char direcao){
 //1 = andar
 //2 = corredor
 int count = 0;
 int state = 0;
 if(lado==1){
 if(corredorAtual+1<=NUM_CORREDORES-1){
 if(predio[andarAtual][corredorAtual+1]=='-'){
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[andarAtual][corredorAtual]){
 if(listaPrioridades[j].movimento=='r'){
 listaPrioridades[j].corredor+=1;
 }
 else if(listaPrioridades[j].movimento=='l'){
 listaPrioridades[j].corredor-=1;
 }
 else{
 listaPrioridades[j].corredor+=1;
 }
 }
 if(elevadores[j].nome==predio[andarAtual][corredorAtual]){
 if(elevadores[j].movimento=='r'){
 elevadores[j].corredor+=1;
 }
 else if(elevadores[j].movimento=='l'){
 elevadores[j].corredor-=1;
 }
 else{
 elevadores[j].corredor+=1;
 }
 }
 }
 predio[andarAtual][corredorAtual]='-';
 state=1;
 }
 substituiElevadores();
 atualizaPredio();
 
 }
 if(corredorAtual-1>=0){
 if(predio[andarAtual][corredorAtual-1]=='-' && state==0){
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[andarAtual][corredorAtual]){
 if(listaPrioridades[j].movimento=='r'){
 listaPrioridades[j].corredor+=1;
 }
 else{
 listaPrioridades[j].corredor-=1;
 }

 }
 if(elevadores[j].nome==predio[andarAtual][corredorAtual]){
 if(elevadores[j].movimento=='r'){
 elevadores[j].corredor+=1;
 }
 else{
 elevadores[j].corredor-=1;
 }

 }
 }
 predio[andarAtual][corredorAtual]='-';
 }
 substituiElevadores();
 atualizaPredio();
 }
 state = 0;
 if(direcao=='u'){
 while(predio[andarAtual+count][corredorAtual]!='-'){
 if(andarAtual+count+1<TOTAL_ANDARES){
 count++;
 }
 else{
 break;
 }
 }
 for(int i=andarAtual+count; i>andarAtual; i--){
 predio[i][corredorAtual]=predio[i-1][corredorAtual];
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[i][corredorAtual]){
 listaPrioridades[j].andar+=1; 
 }
 if(elevadores[j].nome==predio[i][corredorAtual]){
 elevadores[j].andar+=1;
 }
 }
 } 
 }
 else if(direcao=='d'){
 count = 0; 
 while(predio[andarAtual-count][corredorAtual]!='-'){
 if(andarAtual-count-1>=0){
 count++;
 }
 else{
 break;
 }
 }
 for(int i=andarAtual-count; i<andarAtual; i++){
 predio[i][corredorAtual]=predio[i+1][corredorAtual];
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[i][corredorAtual]){
 listaPrioridades[j].andar-=1; 
 }
 if(elevadores[j].nome==predio[i][corredorAtual]){
 elevadores[j].andar-=1;
 }
 }
 } 
 }
 }
 else{
 if(andarAtual+1<=TOTAL_ANDARES-1){
 if(predio[andarAtual+1][corredorAtual]=='-'){
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[andarAtual][corredorAtual]){
 if(listaPrioridades[j].movimento=='u'){
 listaPrioridades[j].andar+=1;
 }
 else if(listaPrioridades[j].movimento=='d'){
 listaPrioridades[j].andar-=1;
 }
 else{
 listaPrioridades[j].andar+=1;
 }

 }
 if(elevadores[j].nome==predio[andarAtual][corredorAtual]){
 if(elevadores[j].movimento=='u'){
 elevadores[j].andar+=1;
 }
 else if(elevadores[j].movimento=='d'){
 elevadores[j].andar-=1;
 }
 else{
 elevadores[j].andar+=1;
 }

 }
 }
 predio[andarAtual][corredorAtual]='-';
 state=1;
 }
 substituiElevadores();
 atualizaPredio();
 }
 if(andarAtual-1>=0){
 if(predio[andarAtual-1][corredorAtual]=='-' && state==0){
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[andarAtual][corredorAtual]){
 if(listaPrioridades[j].movimento=='u'){
 listaPrioridades[j].andar+=1;
 }
 else{
 listaPrioridades[j].andar-=1;
 }

 }
 if(elevadores[j].nome==predio[andarAtual][corredorAtual]){
 if(elevadores[j].movimento=='u'){
 elevadores[j].andar+=1;
 }
 else{
 elevadores[j].andar-=1;
 }
 }
 }
 predio[andarAtual][corredorAtual]='-';
 }
 substituiElevadores();
 atualizaPredio();
 }
 if(direcao=='u'){
 count = 0; 
 while(predio[andarAtual][corredorAtual+count]!='-'){
 if(corredorAtual+count+1<NUM_CORREDORES){
 count++;
 }
 else{
 break;
 }
 }
 for(int i=corredorAtual+count; i>corredorAtual; i--){
 predio[andarAtual][i]=predio[andarAtual][i-1];
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[andarAtual][i]){
 listaPrioridades[j].corredor+=1; 
 }
 if(elevadores[j].nome==predio[andarAtual][i]){
 elevadores[j].corredor+=1;
 }
 }
 } 
 }
 else if(direcao=='d'){
 count = 0; 
 while(predio[andarAtual][corredorAtual-count]!='-'){
 if(corredorAtual-count-1>=0){
 count++;
 }
 else{
 break;
 }
 }
 for(int i=corredorAtual-count; i<corredorAtual; i++){
 predio[andarAtual][i]=predio[andarAtual][i+1];
 for(int j=0; j<NUM_ELEVADORES; j++){
 if(listaPrioridades[j].nome==predio[andarAtual][i]){
 listaPrioridades[j].corredor-=1; 
 }
 if(elevadores[j].nome==predio[andarAtual][i]){
 elevadores[j].corredor-=1;
 }
 }
 } 
 }
 }
 substituiElevadores();
 atualizaPredio();
}

void calculaProximidade(){
 int distancia=300;
 for(int i=0; i<NUM_ELEVADORES; i++){
 if(abs(elevadores[i].andar-ANDAR)+abs(elevadores[i].corredor-CORREDOR)<distancia && (elevadores[i].estado==0 || elevadores[i].estado==3)){
 if(countPrior<=14){
 listaPrioridades[countPrior]=elevadores[i];
 distancia=abs(elevadores[i].andar-ANDAR)+abs(elevadores[i].corredor-CORREDOR);
 }
 else{
 listaEspera[countEspera]=elevadores[i];
 distancia=abs(elevadores[i].andar-ANDAR)+abs(elevadores[i].corredor-CORREDOR);
 }
 }
 }
 if(countPrior<=14){
 listaPrioridades[countPrior].andarDestino=ANDAR;
 listaPrioridades[countPrior].corredorDestino=CORREDOR;
 listaPrioridades[countPrior].estado=1;
 countPrior++;
 }
 else{
 printf("\nElevadores ocupados, andar colocado na lista de espera.\n");
 listaEspera[countEspera].andarDestino=ANDAR;
 listaEspera[countEspera].corredorDestino=CORREDOR;
 listaEspera[countEspera].estado=0;
 countEspera++;
 }
}
//S 10 0 S 8 0 S 290 2 S 9 2
void moveElevadores(){
 int entrou=0;
 for(int i=0; i<countPrior; i++){
 if(listaPrioridades[i].andar-listaPrioridades[i].andarDestino>0){
 listaPrioridades[i].movimento='d';
 }
 else if(listaPrioridades[i].andar-listaPrioridades[i].andarDestino<0){
 listaPrioridades[i].movimento='u';
 }
 else if(listaPrioridades[i].corredor-listaPrioridades[i].corredorDestino>0){
 listaPrioridades[i].movimento='l';
 }
 else if(listaPrioridades[i].corredor-listaPrioridades[i].corredorDestino<0){
 listaPrioridades[i].movimento='r';
 }
 else{
 listaPrioridades[i].movimento='p';
 }
 if(listaPrioridades[i].andar-listaPrioridades[i].andarDestino>0){
 if(listaPrioridades[i].andar-1>=0){
 if(predio[listaPrioridades[i].andar-1][listaPrioridades[i].corredor]!='-'){
 deslocamento(listaPrioridades[i].andar-1,listaPrioridades[i].corredor, 1, listaPrioridades[i].movimento);
 entrou=1;
 }
 }
 if(entrou==0){
 listaPrioridades[i].andar--;
 substituiElevadores();
 atualizaPredio();
 }
 entrou=0;
 }
 else if(listaPrioridades[i].andar-listaPrioridades[i].andarDestino<0){
 if(listaPrioridades[i].andar+1<TOTAL_ANDARES){
 if(predio[listaPrioridades[i].andar+1][listaPrioridades[i].corredor]!='-'){
 deslocamento(listaPrioridades[i].andar+1,listaPrioridades[i].corredor, 1, listaPrioridades[i].movimento);
 entrou=1;
 }
 }
 if(entrou==0){
 listaPrioridades[i].andar++;
 substituiElevadores();
 atualizaPredio();
 }
 entrou=0;
 }
 else{
 if(listaPrioridades[i].corredor-listaPrioridades[i].corredorDestino>0){
 if(listaPrioridades[i].corredor-1>=0){
 if(predio[listaPrioridades[i].andar][listaPrioridades[i].corredor-1]!='-'){
 deslocamento(listaPrioridades[i].andar,listaPrioridades[i].corredor-1, 2, listaPrioridades[i].movimento);
 entrou=1;
 }
 }
 if(entrou==0){
 listaPrioridades[i].corredor--;
 substituiElevadores();
 atualizaPredio();
 }
 entrou=0;
 }
 else if(listaPrioridades[i].corredor-listaPrioridades[i].corredorDestino<0){
 if(listaPrioridades[i].corredor-1<=2){
 if(predio[listaPrioridades[i].andar][listaPrioridades[i].corredor+1]!='-'){
 deslocamento(listaPrioridades[i].andar,listaPrioridades[i].corredor+1, 2, listaPrioridades[i].movimento);
 entrou=1;
 }
 }
 if(entrou==0){
 listaPrioridades[i].corredor++;
 substituiElevadores();
 atualizaPredio();
 }
 }
 else{
 if(listaPrioridades[i].estado==1){
 listaPrioridades[i].estado=2;
 printf("\nO elevador %c chegou na origem (Andar: %d e Corredor: %d). Qual o local de destino? (Andar e Corredor): ",listaPrioridades[i].nome, listaPrioridades[i].andarDestino, listaPrioridades[i].corredorDestino);
 scanf("%d %d", &ANDAR, &CORREDOR);
 listaPrioridades[i].andarDestino=ANDAR;
 listaPrioridades[i].corredorDestino=CORREDOR;
 }
 else if(listaPrioridades[i].estado==2 || listaPrioridades[i].estado==3){
 if(listaPrioridades[i].andarDestino!=listaPrioridades[i].andarInit){
 listaPrioridades[i].estado==3;
 listaPrioridades[i].andarDestino=listaPrioridades[i].andarInit;
 
 }
 if(listaPrioridades[i].corredorDestino!=listaPrioridades[i].corredorInit){
 listaPrioridades[i].estado==3;
 listaPrioridades[i].corredorDestino=listaPrioridades[i].corredorInit;
 }
 if(listaPrioridades[i].andar==listaPrioridades[i].andarDestino && listaPrioridades[i].corredor==listaPrioridades[i].corredorDestino){
 listaPrioridades[i].estado=0;
 substituiElevadores();
 atualizaPredio();
 for(int k=i; k<NUM_ELEVADORES-1; k++){
 if(k+1<15){
 listaPrioridades[k]=listaPrioridades[k+1];
 }
 else{
 listaPrioridades[k].nome=listaEspera[0].nome;
 listaPrioridades[k].andarInit=listaEspera[0].andarInit;
 listaPrioridades[k].corredorInit=listaEspera[0].corredorInit;
 listaPrioridades[k].andar=listaEspera[0].andar;
 listaPrioridades[k].corredor=listaEspera[0].corredor;
 listaPrioridades[k].estado=listaEspera[0].estado;
 listaPrioridades[k].andarDestino=listaEspera[0].andarDestino;
 listaPrioridades[k].corredorDestino=listaEspera[0].corredorDestino;
 for(int l=0; l<countEspera; l++){
 listaEspera[l]=listaEspera[l+1];
 }
 }
 }
 countPrior--;
 countEspera--;
 i--;
 }
 }
 }
 }
 }
}

void chamada(){
 char taChamando;
 imprimePredio();
 printf("\nHá uma nova chamada?(S/N)");
 scanf(" %c", &taChamando);
 if(taChamando=='S'){
 printf("\nOnde o elevador foi chamado(Andar e Corredor): ");
 scanf("%d %d", &ANDAR, &CORREDOR);
 calculaProximidade();
 }
 substituiElevadores();
 atualizaPredio();
 moveElevadores();
 chamada();
}

int main() {
 inicializarElevadores();
 inicializarPredio();
 chamada();
 return 0;
}

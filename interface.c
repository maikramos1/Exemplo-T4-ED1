#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "interface.h"

void ImprimeLista(Tno *lista, int tipo) {
  Tno *aux = lista;
  Tcarta carta[5];
  int i=0,j,tamanho=0;
  switch(tipo){
    case 1:
      //Simples
      if(!ListaVazia(aux)){
        while (!ListaVazia(aux)) {
          printf("│%2s-%c ", aux->carta.face, aux->carta.naipe);
          aux = aux->prox;
        }
        printf("│");
      }
      break;
    case 2:
      //Perfumaria
      if(!ListaVazia(aux)){
        while (!ListaVazia(aux)){
          carta[tamanho] = aux->carta;
          aux = aux->prox;
          tamanho++;
        }
      }
      printf("\t\t");
      for(i=0;i<tamanho;i++) printf("┌─────┐ ");
      printf("\n\t\t");
      for(i=0;i<tamanho;i++){
        if(carta[i].valor == 10){
          if(carta[i].naipe == 'C' || carta[i].naipe == 'O'){
            printf("│\033[1;31m%s\033[0m   │ ",carta[i].face);
          }else{
            printf("│%s   │ ",carta[i].face);
          }

        }else{
          if(carta[i].naipe == 'C' || carta[i].naipe == 'O'){
            printf("│\033[1;31m%s\033[0m    │ ",carta[i].face);
          }else{
            printf("│%s    │ ",carta[i].face);
          }
        }
      }
      printf("\n\t\t");
      for(i=0;i<tamanho;i++){
        if(carta[i].naipe == 'C' || carta[i].naipe == 'O'){
          printf("│  \033[1;31m%s\033[0m  │ ",carta[i].naipeP);
        }else{
          printf("│  %s  │ ",carta[i].naipeP);
        }
      }
      printf("\n\t\t");
      for(i=0;i<tamanho;i++){
        if(carta[i].valor == 10){
          if(carta[i].naipe == 'C' || carta[i].naipe == 'O'){
            printf("│   \033[1;31m%s\033[0m│ ",carta[i].face);
          }else{
            printf("│   %s│ ",carta[i].face);
          }
        }else{
          if(carta[i].naipe == 'C' || carta[i].naipe == 'O'){
            printf("│    \033[1;31m%s\033[0m│ ",carta[i].face);
          }else{
            printf("│    %s│ ",carta[i].face);
          }
        }
      }
      printf("\n\t\t");
      for(i=0;i<tamanho;i++) printf("└─────┘ ");
      //Perfumaria
      break;
    default:
      break;
  } 
}

void ImprimePrimFila(tFila *fila, int tipo){
  tNoFila *aux = fila->prim;
  if (aux != NULL){ 
    switch(tipo){
      case 1:
        printf("(P:%d, E:%d, O:%d, C:%d).",aux->paus,aux->espadas,aux->ouros,aux->copas);
        break;
  
      case 2:
        printf("(\u2663:%2d, \u2660:%2d, \033[1;31m\u2666\033[0m:%2d, \033[1;31m\u2665\033[0m:%2d). ",aux->paus,aux->espadas,aux->ouros,aux->copas);
        break;
  
      default:
        break;
    }
  }
}

void Menu1(){
  printf("\nSelecione seu modo de jogo\n");
  printf("1 - Simples\n");
  printf("2 - COM PERFUMARIAS\n");
  printf("3 - Sair\n");
  printf("Digite a opção desejada: ");
}

void Menu2(int tipo){
  switch(tipo){
    case 1:
      printf("\nMenu Modo Simples:\n");
      printf("1 - Iniciar\n");
      printf("2 - Voltar ao menu anterior\n");
      printf("Digite a opção desejada: ");
      break;

    case 2:
      printf("\n");
      system("clear");
      printf("♣ ♠ ♦ ♥ ♣ ♠ ♦ ♥ ♣ ♠ ♣ ♥ ♦ ♠ ♣ ♥ ♦ ♠ ♣\n");
      printf("♠ ♦ ♥ ♣  CHOOSE YOUR DESTINY  ♣ ♥ ♦ ♠\n");
      printf("♦ ♥ ♣ ♠ ♦ ♥ ♣ ♠ ♦ ♥ ♦ ♠ ♣ ♥ ♦ ♠ ♣ ♥ ♦\n");
      printf("1 - Iniciar\n");
      printf("2 - Voltar ao menu anterior\n");
      printf("Digite a opção desejada: ");
      break;

    default:
      break;
  }
  
}

void Menu3(int tipo){
  switch(tipo){
    case 1:
      printf("Deseja receber o bônus em qual naipe?\n");
      printf("1 - Paus\n");
      printf("2 - Espadas\n");
      printf("3 - Ouros\n");
      printf("4 - Copas\n");
      printf("Digite a opção desejada: ");
      break;

    case 2:
      printf("Deseja receber o bônus em qual naipe?\n");
      printf("1 - \u2663\n");
      printf("2 - \u2660\n");
      printf("3 - \033[1;31m\u2666\033[0m\n");
      printf("4 - \033[1;31m\u2665\033[0m\n");
      printf("Digite a opção desejada: ");
      break;

    default:
      break;
    
  }
}

void FinalPerfumado(int ptfinal, int turno){
  int i;
  char *rgb[3] = {"\033[1;31m","\033[1;32m","\033[1;34m"};
  for(i=0;;i++){
    system("clear");
    printf("%s♣ ♠ ♦ ♥ ♣ ♠ ♦ ♥ ♣ ♠ ♣ ♥ ♦ ♠ ♣ ♥ ♦ ♠ ♣\033[0m\n",rgb[i%3]);
    printf("%s♠           Fim de Jogo !           ♠\033[0m\n",rgb[(i+1)%3]);
    printf("%s♦ ♥ ♣ ♠ ♦ ♥ ♣ ♠ ♣ ♥ ♦ ♠ ♣ ♥ ♦ ♠ ♣ ♥ ♦\033[0m\n",rgb[(i+2)%3]);
    printf("%s♣    Pontuação Final    : %4d      ♣\033[0m\n",rgb[i%3],ptfinal);
    printf("%s♠   Encerrado no Turno  :   %2d      ♠\033[0m\n",rgb[(i+1)%3],turno-1);
    printf("%s♦ ♥ ♣ ♠ ♦ ♥ ♣ ♠ ♣ ♥ ♦ ♠ ♣ ♥ ♦ ♠ ♣ ♥ ♦\033[0m\n",rgb[(i+2)%3]);
    sleep(1);
  }
}
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tno *CriaLista() {
  Tno *lista = NULL;
  return lista;
}

int ListaVazia(Tno *lista) {
  if (lista == NULL)
    return 1;
  else
    return 0;
}

void LiberaLista(Tno **lista) {
  Tno *aux;
  while (!ListaVazia(*lista)) {
    aux = (*lista)->prox;
    free(*lista);
    (*lista) = aux;
  }
}

Tno *CriaNo(Tcarta carta){
  Tno *novo = malloc(sizeof(Tno)); 
  strcpy(novo->carta.face, carta.face);
  novo->carta.naipe = carta.naipe;
  novo->carta.valor = carta.valor;
  strcpy(novo->carta.nome, carta.nome);
  strcpy(novo->carta.naipeP, carta.naipeP);
  novo->prox = NULL;
  return novo;
}

void InsereNo(Tno **lista, Tno *novoNo, int pos){
  int i=1;
  Tno *aux, **aux2;

  aux2 = lista;
  while(i < pos && (*aux2) != NULL){
    aux2 = (Tno**) &((*aux2)->prox);
    i++;
  }
  aux = novoNo;
  aux->prox = (*aux2);
  (*aux2) = aux;
}

Tno *RemoveNo(Tno **lista, int pos){
  int i;
  Tno *aux, *aux2;
  aux = (*lista);
  if(pos == 1){
    (*lista) = aux->prox;
    aux->prox = NULL;
    return aux;
  } else{
    for(i=1; i<pos-1;i++) aux = aux->prox;
    aux2 = aux->prox;
    aux->prox = aux2->prox;
    aux2->prox = NULL;
    return aux2;
  }
}

Tno *AcessaNo(Tno *lista, int pos){
  int i;
  Tno *aux = lista;
  for(i=0; i<pos-1;i++) aux = aux->prox;
  return aux;
}

void MudaPos(Tno **lista, int posOrig, int posDest){
  Tno *aux = RemoveNo(lista, posOrig);
  InsereNo(lista, aux, posDest);
}

void MudaLista(Tno **listaOrig, Tno **listaDest, int tamanho){
  Tno *aux = RemoveNo(listaOrig, 1);
  InsereNo(listaDest,aux,tamanho);
}

int TamanhoLista(Tno *lista){
  int i=1;
  Tno *aux = lista;
  if(ListaVazia(lista)){
    return 0;
  }else{
    if(aux->prox == NULL){
      return 1;
    }else{
      while(aux->prox != NULL){
        aux = aux->prox;
        i++;
      }
      return i;
    }
  }
}
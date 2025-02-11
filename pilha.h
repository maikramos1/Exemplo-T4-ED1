#include "lista.h"

#ifndef PILHA
#define PILHA
typedef Tno tNoPilha;

typedef struct _pilha{
  tNoPilha *topo;
  tNoPilha *base;
}tPilha;
#endif

tPilha *CriaPilha();
int PilhaVazia(tPilha *pilha);
void LiberaPilha(tPilha *pilha);
void InsereNoPilha(tPilha *pilha, tNoPilha *novoNo);
tNoPilha *RemoveNoPilha(tPilha *pilha);
tNoPilha *AcessaTopoPilha(tPilha *pilha);
int TamanhoPilha(tPilha *pilha);
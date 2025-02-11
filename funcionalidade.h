#include "lista.h"
#include "fila.h"
#include "pilha.h"

#ifndef REC
#define REC
typedef struct recurso{
  int paus;
  int espadas;
  int ouros;
  int copas;
}tRec;
#endif

void Reembaralhar(tPilha *monte, tPilha *descarte);
void ReembaralharTudo(Tno **mao, tPilha *monte, tPilha *descarte);
void PreencheMao(tPilha *pilha, Tno **lista, int tamanho);
int ContaBonus(Tno *lista, int tamanho);
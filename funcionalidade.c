#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionalidade.h"

int aleatorio(int n) {
  srand(time(NULL));
  if(n==1) return 1;
  return n = (rand() % (n+1));
};

void Reembaralhar(tPilha *monte, tPilha *descarte){
  int i,tamanho;
  Tno *aux = CriaLista();

  tamanho = TamanhoPilha(monte) + TamanhoPilha(descarte);

  while(TamanhoLista(aux)<tamanho){
    if(!PilhaVazia(monte)) InsereNo(&aux,RemoveNoPilha(monte),1);
    if(!PilhaVazia(descarte)) InsereNo(&aux,RemoveNoPilha(descarte),1);
  }

  for(i=0;i<tamanho;i++){
    InsereNoPilha(monte, RemoveNo(&aux, aleatorio(TamanhoLista(aux))));
  }

  free(aux);
}

void ReembaralharTudo(Tno **mao, tPilha *monte, tPilha *descarte){
  int i,tamanho = 52;
  Tno *lista = CriaLista();


  while(TamanhoLista(lista)<tamanho){
    if(!PilhaVazia(monte)) InsereNo(&lista,RemoveNoPilha(monte),1);
    if(!PilhaVazia(descarte)) InsereNo(&lista,RemoveNoPilha(descarte),1);
    if(!(ListaVazia(*mao))) InsereNo(&lista,RemoveNo(mao,1),1);
  }

  for(i=0;i<tamanho;i++){
    InsereNoPilha(monte, RemoveNo(&lista, aleatorio(TamanhoLista(lista))));
  }

  free(lista);
}

void PreencheMao(tPilha *pilha, Tno **lista, int tamanho){
  int t = tamanho;

  while(t>0){
    if(!PilhaVazia(pilha)){
      InsereNo(lista,RemoveNoPilha(pilha),5);
    }
    t--;
   }

}

int ContaBonus(Tno *lista, int tamanho){
  int i,pt=0,sequencia=0,naipe=0,np=0,ne=0,no=0,nc=0;
  Tcarta aux[5];

  //bota na variavel auxiliar pra facilitar a visualização da conta
  for(i=0;i<tamanho;i++) aux[i] = AcessaNo(lista,i+1)->carta;

  for(i=0;i<tamanho;i++){

    //testando se é par
    if(aux[i].valor == aux[i+1].valor && i+1<tamanho){
      pt+=2;

      //se for um par, entao testa se é uma trinca
      if(aux[i].valor == aux[i+2].valor && i+2<tamanho){
        pt+=3;

        //se for uma trinca, testa se é uma quadra
        if (aux[i].valor == aux[i+3].valor && i+3<tamanho){
          pt+=15;
          i++;
        }
        i++;
      }
    }
  }

  //testando sequencia a partir da primeira carta
  for(i=0;i<tamanho;i++) {
    if(aux[i].valor == aux[i+1].valor-1 && i+1<tamanho){
      if(!sequencia || aux[i].valor != aux[i-1].valor+1) sequencia++;
      sequencia++;
    }
  }

  //testando naipe
  for(i=0;i<tamanho;i++){
    switch(aux[i].naipe){
      case 'P':
        np++;
        break;
      case 'E':
        ne++;
        break;
      case 'O':
        no++;
        break;
      case 'C':
        nc++;
        break;
      default:
        break;
    }
  }
  if(np>=2) naipe+=np;
  if(ne>=2) naipe+=ne;
  if(no>=2) naipe+=no;
  if(nc>=2) naipe+=nc;

  //converte para pontos
  if(sequencia>=2) pt+=(2*sequencia);
  pt+=(3*naipe); 

  if (pt==0){
    //só aparecer no modo simples
    printf("Nenhum bônus alcançado.\n");
  }else{
    printf("Bônus alcançado: %d\n",pt);
  }
  return pt;
}
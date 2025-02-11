/*Nome: Maik Ramos Maifredo. 
Matrícula 2022200556.

checkpoint do motoqueiro fantasma brasileiro

Olá professor, esse código é o mesmo da entrega 4
caso já tenha feito a correção do T4 olhando os requisitos do TF já da pra pular a correção desse código
bom descanso*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "interface.h"
#include "funcionalidade.h"

int main(void) {
  int i, menu1, menu2, menu3, posorigem, posdestino, bonus = 0, pt=0, qdescarte=0, qdescartetemp=0, remb=0, trn=1, trntarefa=0, ptfinal=0, rect=0, recn=0, recr=0, nt=0;
  tRec recursos = {0,0,0,0};
  Tcarta carta;
  tNoFila nosolto;
  Tno *lista = CriaLista(), *mao = CriaLista(), *descartetemp = CriaLista();
  tFila *filatarefas = CriaFila();
  tPilha *monte = CriaPilha(), *descarte = CriaPilha();
  Tno *aux;
  FILE *baralho = fopen("baralho.dat", "r");
  FILE *tarefas = fopen("tarefas.dat","r");

  //ler arquivo e armazenar na lista
  for (i=1;i<53;i++){
    fscanf(baralho,"%2s %c %d %[^\n]s", carta.face, &carta.naipe, &carta.valor, carta.nome);

    //perfumaria naipe unicode
    switch(carta.naipe){
      case 'P':
        strcpy(carta.naipeP, "\u2663");
        break;
      
      case 'C':
        strcpy(carta.naipeP, "\u2665");
        break;
      
      case 'E':
        strcpy(carta.naipeP, "\u2660");
        break;
      
      case 'O':
        strcpy(carta.naipeP, "\u2666");
        break;
      
      default:
        break;
    }
    InsereNo(&lista, CriaNo(carta), i);
  }
  ReembaralharTudo(&lista, monte, descarte);

  //ler arquivo e armazenar na fila
  for(i=0;i<10;i++){
    fscanf(tarefas,"%d %d %d %d %d %d %d", &nosolto.turno, &nosolto.prazo, &nosolto.paus, &nosolto.espadas, &nosolto.ouros, &nosolto.copas, &nosolto.premio);
    
    InsereNoFila(filatarefas,CriaNoFila(nosolto));
  }

  printf("Bem-vindo(a)!\n");
  do{
    Menu1();
    
    scanf("%d", &menu1);
    
    switch(menu1){
      case 1 ... 2:
        do{
          Menu2(menu1);
          
          scanf("%d", &menu2);
          
          switch(menu2){
            case 1:
              //completa a mão com 5 cartas
              PreencheMao(monte,&mao,5);
              
              //começa o jogo
              do{
                switch(menu1){
                  case 1:
                    printf("\nP:%2d  -  E:%2d  -  O:%2d  -  C:%2d  -  *:%2d\t\t     (%d) \n\n", recursos.paus, recursos.espadas, recursos.ouros, recursos.copas, remb, trn);
                    
                    printf("Tarefas: ");
                    
                    if(!FilaVazia(filatarefas)){
                      if(filatarefas->prim->turno <= trn){
                        trntarefa = filatarefas->prim->turno + filatarefas->prim->prazo - trn;
                        
                        printf("%d ",trntarefa);
                        
                        ImprimePrimFila(filatarefas,menu1);
                        
                      }else{
                        printf("Nenhuma tarefa no momento!");
                      }
                    }else{
                      printf("Fim das tarefas!");
                    }
                    
                    printf("\n\n\nMonte (%d)\t\t\t\t\t\t\t\t\tDescarte (%d)",TamanhoPilha(monte),TamanhoPilha(descarte));
                    
                    printf("\n\n\t");
                    ImprimeLista(mao,menu1);
                    printf("\nMão :  ");
                    
                    for (i=0;i<TamanhoLista(mao);i++) printf("%d     ",i+1);
                    break;

                  case 2:
                    system("clear");
                    printf("\u2663: %d  ━━  \u2660: %d  ━━  \033[1;31m\u2666\033[0m: %d  ━━  \033[1;31m\u2665\033[0m: %d  ━━  *: %d\t\t (%d)\n\n", recursos.paus, recursos.espadas, recursos.ouros, recursos.copas, remb, trn);
                    printf("Tarefas: ");
                    
                    if(!FilaVazia(filatarefas)){
                      
                      if(filatarefas->prim->turno <= trn){
                        trntarefa = filatarefas->prim->turno + filatarefas->prim->prazo - trn;
                        
                        printf("%d ",trntarefa);
                        ImprimePrimFila(filatarefas,menu1);
                        
                      }else{
                        printf("Nenhuma tarefa no momento!");
                      }
                      
                    }else{
                      printf("Fim das Tarefas!");
                    }
                    
                    printf("\n\n\nMonte (%d)\t\t\t\t\t\t\t\t\tDescarte (%d)",TamanhoPilha(monte),TamanhoPilha(descarte));
                    
                    printf("\n\n");
                    ImprimeLista(mao,menu1);
                    printf("\n\tMão:   ");
                    
                    for (i=0;i<TamanhoLista(mao);i++) printf("%d\t   ",i+1);
                    break;

                  default:
                    break;
                }
                
                //Interface(menu1,remb,trn,nt,recursos,*filatarefas,*monte,*descarte,*mao);
                printf("\n\nMenu:\n\n");
                printf("1 − Reposicionar carta\n");
                printf("2 - Descartar cartas\n");
                printf("3 - Cumprir tarefa\n");
                printf("4 - Reembaralhar tudo (*:%d)\n",remb);
                if(FilaVazia(filatarefas)){
                  printf("5 - Encerrar jogo\n\n");
                }else{
                  printf("5 - Finalizar turno\n\n");
                }
                
                switch(nt){
                  case 0:
                    printf("\n");
                    break;

                  case 1:
                    printf("Tarefa cumprida com sucesso!\n");
                    nt=0;
                    break;

                  case 2:
                    printf("Nenhuma tarefa ativa no momento!\n");
                    nt=0;
                    break;

                  case 3:
                    printf("Recursos insuficientes!\n");
                    nt=0;
                    break;

                  case 4:
                    printf("Reembaralhamento utilizado!\n");
                    nt=0;
                    break;

                  case 5:
                    printf("Reembaralhamento não disponível!\n");
                    nt=0;
                    break;

                  case 6:
                    printf("Nenhum bônus alcançado.\n");
                    nt=0;
                    break;
                  
                  default:
                    break;
                }
                
                printf("Digite a opção desejada: ");
                scanf("%d", &menu3);
                
                switch(menu3){
                  
                  case 1:
                    //mudar posição
                    printf("Posição de Origem: ");
                    scanf("%d",&posorigem);
                    printf("Posição de Destino: ");
                    scanf("%d",&posdestino);
                    if(posorigem>0 && posorigem<6 && posdestino>0 && posdestino<6 && (!ListaVazia(mao))) MudaPos(&mao, posorigem, posdestino);
                    break;

                  case 2:
                    //descartar carta
                    printf("Descartar quantas cartas? ");
                    scanf("%d",&qdescartetemp);
                    
                    if(qdescartetemp>0 && qdescartetemp<(6-qdescarte) && (qdescartetemp+TamanhoPilha(descarte))<53){
                      
                      for(i=1;i<=qdescartetemp;i++){
                        MudaLista(&mao, &descartetemp, qdescartetemp);
                        carta=AcessaNo(descartetemp,i)->carta;
                        
                        switch(carta.naipe){
                          case 'P':
                            recursos.paus+=carta.valor;
                            break;
                          case 'E':
                            recursos.espadas+=carta.valor;
                            break;
                          case 'O':
                            recursos.ouros+=carta.valor;
                            break;
                          case 'C':
                            recursos.copas+=carta.valor;
                            break;
                          default:
                            break;
                        }
                      }
                      
                      qdescarte+=qdescartetemp;
                      pt+=ContaBonus(descartetemp,qdescartetemp);
                      
                      if(pt){
                        Menu3(menu1);
                        while(pt){
                          scanf("%d",&bonus);
                          
                          switch(bonus){
                            case 1:
                              recursos.paus+=pt;
                              pt=0;
                              break;
                            case 2:
                              recursos.espadas+=pt;
                              pt=0;
                              break;
                            case 3:
                              recursos.ouros+=pt;
                              pt=0;
                            case 4:
                              recursos.copas+=pt;
                              pt=0;
                              break;
                            default:
                              printf("Digite uma opção válida: ");
                              break;
                          }
                        }
                      }else{
                        nt=6;
                      }

                      for(i=1;i<=qdescartetemp;i++){
                        InsereNoPilha(descarte,RemoveNo(&descartetemp,1));
                      }
                    }
                    break;

                  case 3:
                    //Cumprir Tarefa
                    nosolto = *AcessaPrimFila(filatarefas);
                    
                    if(nosolto.turno <= trn && recursos.paus >= nosolto.paus && recursos.espadas >= nosolto.espadas && recursos.ouros >= nosolto.ouros && recursos.copas >= nosolto.copas){
                      
                      recursos.paus -= nosolto.paus;
                      recursos.espadas -= nosolto.espadas;
                      recursos.ouros -= nosolto.ouros;
                      recursos.copas -= nosolto.copas;
                      
                      remb += nosolto.premio;
                      
                      rect += nosolto.paus * trntarefa;
                      rect += nosolto.espadas * trntarefa;
                      rect += nosolto.ouros * trntarefa;
                      rect += nosolto.copas * trntarefa;
                      
                      printf("Tarefa cumprida com sucesso!\n");
                      
                      if(menu1==2) nt=1;
                      
                      RemoveNoFila(filatarefas);
                      
                    }else{
                      
                      if(nosolto.turno > trn){
                        
                        printf("Nenhuma tarefa ativa no momento!\n");
                        if(menu1==2) nt=2;
                        
                      }else{
                        
                        printf("Recursos insuficientes!\n");
                        if(menu1==2) nt=3;
                        
                      }
                    }
                    break;

                  case 4:
                    //Reembaralhar tudo
                    if(remb>0){
                      
                      ReembaralharTudo(&mao,monte,descarte);
                      PreencheMao(monte,&mao,5);
                      remb-=1;
                      qdescarte=0;
                      
                      if(menu1==1) printf("Reembaralhamento realizado com sucesso!\n");
                      if(menu1==2) nt=4;
                      
                    }else{
                      
                      if(menu1==1) printf("Reembaralhamentos insuficientes!\n");
                      if(menu1==2) nt=5;
                      
                    }

                    break;

                  case 5:
                    //Encerrar turno
                    
                    if(PilhaVazia(monte)){

                      ReembaralharTudo(&mao,monte,descarte);
                      PreencheMao(monte,&mao,5);

                    }else{

                      if(qdescarte>TamanhoPilha(monte)){
                        
                        PreencheMao(monte,&mao,qdescarte);
                        Reembaralhar(monte,descarte);
                        qdescarte = TamanhoLista(mao);
                        PreencheMao(monte,&mao,5-qdescarte);
                        
                      }else{
                        PreencheMao(monte,&mao,qdescarte);
                      }
                    }
                    
                    qdescarte = 0;
                    qdescartetemp = 0;
                    trn++;
                    
                    if(!FilaVazia(filatarefas)){

                      if(TamanhoFila(filatarefas) == 1 && (filatarefas->prim->prazo + filatarefas->prim->turno) <= trn ) {
                        
                        nosolto = *RemoveNoFila(filatarefas);
                        recn += (nosolto.paus + nosolto.espadas + nosolto.ouros + nosolto.copas);
                        
                      }
                      
                      while(TamanhoFila(filatarefas)>1){
                        if((filatarefas->prim->prazo + filatarefas->prim->turno) <= trn){
                          nosolto = *RemoveNoFila(filatarefas);
                          recn += (nosolto.paus + nosolto.espadas + nosolto.ouros + nosolto.copas);
                          
                        }else{
                          break;
                        }
                      }
                      
                    }

                    //criterio de encerramento
                    if(FilaVazia(filatarefas)){
                      recr = (recursos.paus + recursos.espadas + recursos.ouros + recursos.copas);
                      ptfinal = (rect + (recr/2)) - (recn);
                      LiberaLista(&lista);
                      LiberaLista(&mao);
                      LiberaLista(&descartetemp);
                      LiberaFila(filatarefas);
                      LiberaPilha(monte);
                      LiberaPilha(descarte);
                      if(menu1==2){
                        FinalPerfumado(ptfinal,trn);
                      }else{
                        printf("\nFim de Jogo!\n");
                        printf("Pontuação final: %d\n", ptfinal);
                      }
                      menu3=6;
                      menu2=2;
                      menu1=3;
                    }
                    break;

                  default:
                    printf("Opção inválida!\n");
                    menu3=7;
                    break;
                }
              }while(menu3!=6);
              break;

            case 2:
              //volta ao menu antenterior
              printf("\nVoltando ao menu anterior\n");
              break;

            default:
              printf("\nOpção Inválida!\n");
              break;
            
          }
          
        }while(menu2!=2);
        break;

      case 3:
        //sair
        printf("\nObrigado por jogar!");
        LiberaLista(&lista);
        LiberaLista(&mao);
        LiberaLista(&descartetemp);
        LiberaFila(filatarefas);
        LiberaPilha(monte);
        LiberaPilha(descarte);
        break;
      
      default:
        printf("\nOpção inválida!\n");
        break;
    
    }
  }while(menu1 != 3);
  
  fclose(baralho);
  fclose(tarefas);

  return 0;
}
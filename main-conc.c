/*
 * Disciplina: Computacao Concorrente
 * Prof.: Silvana Rossetto
 * Trabalho 1
 * Codigo: Problema da quadratura para integracao numerica
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"  //para usar funcoes de medida de tempo

//variaveis globais


/*
 * Funcao que soma os elementos do vetor
 * Entrada: vetor de entrada
 * Saida: soma dos elementos do vetor
 */

 void *Calcula(void *tid) {
   int id = * (int *) tid;
   int i;

 }

//funcao principal
int main(int argc, char *argv[]) {
  pthread_t *tid_sistema;     //vetor de identificadores das threads no sistema
  int *tid;                   //identificadores das threads no programa
  int t;                      //variavel contadora
  double inicio, fim, delta;  //variaveis para medir o tempo de execucao

  //le e valida os parametros de entrada
  if(argc < 4) {
    fprintf(stderr, "Digite: %s <intervalo de integracao> <erro maximo> <numero de threads>.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //numero de threads
  nthreads = atoi(argv[2]);

  //aloca espaco para o vetor de identificadores das threads no sistema
  tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }

  //-----------------------------------------------------------------------------------
  GET_TIME(inicio);

  //cria as threads
  for(t=0; t<nthreads; t++) {
    tid = malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
    *tid = t;

    if (pthread_create(&tid_sistema[t], NULL, Calcula, (void*) tid)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  //espera todas as threads terminarem e imprime o vetor de saída
  for(t=0; t<nthreads; t++) {
    if (pthread_join(tid_sistema[t], NULL)) {
      printf("--ERRO: pthread_join()\n"); exit(-1);
    }
  }

  GET_TIME(fim);

  //exibe os resultados da soma

  //calcula e exibe o tempo gasto com a multiplicacao
  delta = fim - inicio;
  printf("Tempo de calculo da integral: %.8lf\n", delta);

  return 0;
}

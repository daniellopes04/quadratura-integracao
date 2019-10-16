/*
 * Disciplina: Computacao Concorrente
 * Prof.: Silvana Rossetto
 * Trabalho 1
 * Codigo: Problema da quadratura para integracao numerica
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"  //para usar funcoes de medida de tempo

/*
 * Funcao que
 * Entrada:
 * Saida:
 */

 double Calcula(void *) {
   int id = * (int *) tid;
   int i;

 }

//funcao principal
int main(int argc, char *argv[]) {
  double erro, resultado;
  double inicio, fim, delta;  //variaveis para medir o tempo de execucao

  //le e valida os parametros de entrada
  if(argc < 4) {
    fprintf(stderr, "Digite: %s <intervalo de integracao> <erro maximo> <numero de threads>.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //-----------------------------------------------------------------------------------
  GET_TIME(inicio);


  GET_TIME(fim);

  //exibe os resultados da soma

  //calcula e exibe o tempo gasto com a multiplicacao
  delta = fim - inicio;
  printf("Tempo de calculo da integral: %.8lf\n", delta);

  return 0;
}

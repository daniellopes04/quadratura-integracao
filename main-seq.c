/*
 * Disciplina: Computacao Concorrente
 * Prof.: Silvana Rossetto
 * Trabalho 1
 * Codigo: Problema da quadratura para integracao numerica
 * Funcao: f(x) = 1+x
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"  //para usar funcoes de medida de tempo

float erro;                //variavel de erro

/*
 * Funcao cuja integral sera calculada
 * Entrada: X da funcao
 * Saida: Valor da funcao em X
 */

float f(float x) {
  return 1 + x;
  //return sqrt(1 - pow(x,2));
  //return sqrt(1 + pow(x,4));
  //return sin(pow(x,2));
  //return cos(pow(M_E, -x));
  //return cos(pow(M_E, -x)) * x;
  //return cos(pow(M_E, -x)) * ((0.005 * pow(x,3)) + 1);
}

/*
 * Funcao que calcula a integral
 * Entrada: Intervalo inferior e superior
 * Saida: Resultado da integracao
 */

float CalculaIntegral(float x1, float x2) {
  float m, base, dif;
  float area[3];

  m = (x1 + x2)/2;
  base = (x2 - x1)/2;

  //printf("%f  medio\n %f  base\n\n\n", m, base);
  
  area[0] = base*f(m-base);
  area[1] = base*f(m);
  area[2] = base*f(m+base);

  //printf("%f  area0\n%f  area1\n%f  area2\n\n\n", area[0], area[1], area[2]);

  dif = abs(area[2] - (area[0] + area[1]));

  //printf("%f  dif\n\n\n", dif);

  if(dif <= erro)
    return area[2];
  else
  {
    return (CalculaIntegral(x1, m) + CalculaIntegral (m, x2));
  }
  
}

//funcao principal
int main(int argc, char *argv[]) {
  double inicio, fim, delta;  //variaveis para medir o tempo de execucao
  float a, b;                //variaveis de intervalo
  float resultadoFinal;      //variavel para resultado da integracao

  //le e valida os parametros de entrada
  if(argc < 4) {
    fprintf(stderr, "Digite: %s <intervalo inferior de integracao> <intervalo superior de integracao> <erro maximo>.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  a = atof(argv[1]);
  b = atof(argv[2]);

  erro = atof(argv[3]);

  //-----------------------------------------------------------------------------------
  GET_TIME(inicio);

  resultadoFinal = CalculaIntegral(a, b);

  GET_TIME(fim);

  //calcula e exibe o tempo gasto com a multiplicacao
  delta = fim - inicio;
  printf("Tempo de calculo da integral: %.8lf\n", delta);
  printf("Resultado da integracao: %f\n", resultadoFinal);

  return 0;
}

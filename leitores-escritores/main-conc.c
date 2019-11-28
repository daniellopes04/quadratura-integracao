/*
 * Disciplina: Computacao Concorrente
 * Prof.: Silvana Rossetto
 * Trabalho 2
 * Codigo: Problema de leitores e escritores sem inanicao
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int nDeEscritas, nDeLeituras;
int leiturasFeitas = 0, escritasFeitas = 0;
int leitores = 0, escritores = 0, querEscrever = -1, ativou = 0;
int recurso = -1;
sem_t em;
pthread_mutex_t mutex_l, mutex_e;
pthread_cond_t cond, cond2;

void Escrita(){
  print("escreveu\n");
}

int Leitura(){

  printf("leu\n");
  return 0;

}

void * threadEscritora(void * id){

  int * tid = (int * ) id;
  int i = 0;

  while(escritasFeitas < nDeEscritas){

    pthread_mutex_lock(&mutex_e);
    querEscrever = tid;
    sem_wait(&em);
    if(leitores > 0) { pthread_cond_wait(&cond2, &mutex_e); }

    Escrita(tid);

    querEscrever = -1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_lock(&mutex_l);
    ativou = 0;
    pthread_mutex_unlock(&mutex_l);
    pthread_mutex_unlock(&mutex_e);

  }

  free(tid);
  pthread_exit(NULL);

}

void * threadLeitora(void * id){

  int * tid = (int * ) id;
  int i = 0;

  while(leiturasFeitas < nDeLeituras){

    pthread_mutex_lock(&mutex_l);
    if(querEscrever > 0){ if(ativou == 0) { sem_post(&em); ativou = 1; } pthread_cond_wait(&cond, &mutex_l); }
    leitores++;
    pthread_mutex_unlock(&mutex_l);

    Leitura(tid);

    pthread_mutex_lock(&mutex_l);
    leitores--;
    if(querEscrever > 0 && leitores == 0){ pthread_cond_signal(&cond2); }
    pthread_mutex_unlock(&mutex_l);

  }

  free(tid);
  pthread_exit(NULL);

}


//funcao principal
int main(int argc, char *argv[]) {

  int nThreadsEscritoras, nThreadsLeitoras, i;
  int * idThread;
  char * nomeDoArquivo;
  pthread_t * tid;

  sem_init(&em, 0, 1);
  pthread_mutex_init(&mutex_l, NULL);
  pthread_mutex_init(&mutex_e, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_cond_init(&cond2, NULL);

  if(argc < 6) { 
    printf("%s numeroThreadsLeitoras numeroThreadsEscritoras numeroLeituras numeroEscritas Log", argv[0]); exit(-1); 
  }

  nThreadsLeitoras = atoi(argv[1]);
  nThreadsEscritoras = atoi(argv[2]);
  nDeLeituras = atoi(argv[3]);
  nDeEscritas = atoi(argv[4]);
  nomeDoArquivo = argv[5];

  tid = (pthread_t *) malloc (sizeof(pthread_t) * (nThreadsEscritoras + nThreadsLeitoras));

  for(i = 0 ; i < nThreadsEscritoras ; i++){
    
    idThread = malloc(sizeof(int));
    if(idThread == NULL) { printf("falha na alocação de memória\n"); exit(-1); }
    *idThread = i;

    if(pthread_create(&tid[i], NULL, threadEscritora, (void *) idThread)) { printf("erro ao criar thread\n"); exit(-1); }

  }

  for(i = nThreadsEscritoras ; i < (nThreadsLeitoras + nThreadsEscritoras) ; i++){

    idThread = malloc(sizeof(int));
    if(idThread == NULL) { printf("falha na alocação de memória\n"); exit(-1); }
    *idThread = i;

    if(pthread_create(&tid[i], NULL, threadLeitora, (void *) idThread)) { printf("erro ao criar thread\n"); exit(-1); }

  }

  for(i = 0 ; i < (nThreadsEscritoras + nThreadsLeitoras); i++){
    pthread_join(tid[i], NULL);
  }

  printf("Fim da Thread Principal\n");
  free(tid);

  return 0;
}

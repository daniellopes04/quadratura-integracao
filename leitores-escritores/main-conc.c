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
#include <string.h>

int nDeEscritas, nDeLeituras;
int leiturasFeitas = 0, escritasFeitas = 0;
int nThreadsEscritoras, nThreadsLeitoras;
int leitores = 0, escritores = 0;
int leitor = -1, escritor = -1;
int recurso = -1;
int threads = 0;
pthread_mutex_t readerMutex, barrierMutex;
pthread_cond_t cond;
sem_t em, fila;

FILE ** files;
FILE * logger;

void barreira(){

  pthread_mutex_lock(&barrierMutex);
  threads++;
  if (threads < (nThreadsEscritoras + nThreadsLeitoras)) { pthread_cond_wait(&cond, &barrierMutex); }
  else { pthread_cond_broadcast(&cond); }
  pthread_mutex_unlock(&barrierMutex);

}

void Escrita(int idThreadEscritora){
  
  recurso = idThreadEscritora;

}

int Leitura(int idThreadLeitora){

  fprintf(files[idThreadLeitora - nThreadsEscritoras], "Thread %d leu o valor %d\n", idThreadLeitora, recurso);

  return 0;

}

void * threadEscritora(void * id){

  int * tid = (int * ) id;
  barreira();

  while(escritasFeitas < nDeEscritas){;

    sem_wait(&fila);
    sem_wait(&em);
    escritor = *tid;
    if(leitores > 0) { fprintf(logger, "leituraBloqueada(%d)\n", leitor); }
    fprintf(logger, "entraEscrita(%d)\n", *tid);
    sem_post(&fila);

    Escrita(*tid);

    escritasFeitas++;
    fprintf(logger, "saiEscrita(%d)\n", *tid);

    sem_post(&em);

  }

  free(tid);
  pthread_exit(NULL);

}

void * threadLeitora(void * id){

  int * tid = (int * ) id;
  barreira();

  while(leiturasFeitas < nDeLeituras){

    sem_wait(&fila);
    pthread_mutex_lock(&readerMutex);
    if(leitores == 0){ sem_wait(&em); }
    leitor = *tid;
    if(escritores > 0) { fprintf(logger, "escritaBloqueada(%d)\n", escritor); }
    fprintf(logger, "entraLeitura(%d)\n", *tid);
    leitores++;
    sem_post(&fila);
    pthread_mutex_unlock(&readerMutex);

    Leitura(*tid);

    pthread_mutex_lock(&readerMutex);
    leitores--;
    leiturasFeitas++;
    fprintf(logger, "saiLeitura(%d, %d)\n", *tid, recurso);
    if(leitores == 0) { sem_post(&em); }
    pthread_mutex_unlock(&readerMutex);

  }

  free(tid);
  pthread_exit(NULL);

}

//funcao principal
int main(int argc, char *argv[]) {

  int i;
  int * idThread;
  char * nomeDoArquivo;
  pthread_t * tid;
  FILE * tempFile;
  
  if(argc < 6) { 
    printf("\nDigite: %s numeroThreadsLeitoras numeroThreadsEscritoras numeroLeituras numeroEscritas nomeArquivoLog\n\n", argv[0]); exit(-1); 
  }

  pthread_mutex_init(&readerMutex, NULL);
  pthread_mutex_init(&barrierMutex, NULL);
  pthread_cond_init(&cond, NULL);
  sem_init(&em, 0, 1);
  sem_init(&fila, 0, 1);

  nThreadsLeitoras = atoi(argv[1]);
  nThreadsEscritoras = atoi(argv[2]);
  nDeLeituras = atoi(argv[3]);
  nDeEscritas = atoi(argv[4]);
  nomeDoArquivo = argv[5];

  files = malloc (sizeof(FILE *) * nThreadsLeitoras);
  
  strcat(nomeDoArquivo, ".txt");
  logger = fopen(nomeDoArquivo, "w");
  tempFile = fopen("temp.txt", "w");

  fprintf(tempFile, "%s", nomeDoArquivo);

  //printa no arquivo de log os parametros iniciais do programa passados na linha de comando
  fprintf(logger, "iniciaVerificacao(%d, %d, %d, %d)\n", nThreadsLeitoras, nThreadsEscritoras, nDeLeituras, nDeEscritas);

  tid = (pthread_t *) malloc (sizeof(pthread_t) * (nThreadsEscritoras + nThreadsLeitoras));

  for(i = 0 ; i < nThreadsEscritoras ; i++){
    
    idThread = malloc(sizeof(int));
    if(idThread == NULL) { printf("\nErro: falha na alocação de memória\n\n"); exit(-1); }
    *idThread = i;

    if(pthread_create(&tid[i], NULL, threadEscritora, (void *) idThread)) { printf("\nErro: falha ao criar thread\n\n"); exit(-1); }

  }

  for(i = nThreadsEscritoras ; i < (nThreadsLeitoras + nThreadsEscritoras) ; i++){

    char string[10];

    idThread = malloc(sizeof(int));
    if(idThread == NULL) { printf("\nErro: falha na alocação de memória\n\n"); exit(-1); }
    *idThread = i;

    sprintf(string, "%d.txt", i);
    
    files[i - nThreadsEscritoras] = fopen(string, "w");

    if(pthread_create(&tid[i], NULL, threadLeitora, (void *) idThread)) { printf("\nErro: falha ao criar thread\n\n"); exit(-1); }

  }

  for(i = 0 ; i < (nThreadsEscritoras + nThreadsLeitoras); i++){
    pthread_join(tid[i], NULL);
  }

  printf("\nFim da Thread Principal\n\n");
  free(tid);

  return 0;
}

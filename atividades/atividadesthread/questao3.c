#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int k; // Booleano para verificar se o número é primo
int f; // Dado compartilhado entre as threads
void *funcaof(void *param); //Assinatura da função que será executada pela thread.
void *funcaok(void *param);

int main(int argc, char *argv[]){
    if (argc != 2 && atoi(argv[1]) < 0) {
	    fprintf(stderr,"sintaxe: ./criandothreads <valor inteiro maior que 0>\n");
	    return -1;}

    pthread_t thread1; //cria variável do tipo thread
    pthread_t thread2;
    pthread_attr_t attr; // cria variável do tipo atributo de thread
    pthread_attr_init(&attr); // inicializa attr com valores padroes

    pthread_create(&thread1,&attr,funcaof,argv[1]); // cria a thread
    pthread_create(&thread2,&attr,funcaok,argv[1]);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("f = %d\n",f);
    if (k){
      printf("k = true\n");
    }else{
      printf("k = false\n");
    }
    
}

void *funcaof(void *param) {
    int i, ultimo = atoi(param);
    f = 0;

	if (ultimo > 0)
		for (i = 1; i <= ultimo; i++)
			f += i;

  pthread_exit(0);
}

void *funcaok(void *param){
  int N = atoi(param);
  if (N == 1)
    k = 0;
  else
    k = 1;
  for (int i=2; i <= N/2; i++){
    if (N % i == 0){
        k = 0;
        break;
    } 
  } 

  pthread_exit(0);
}

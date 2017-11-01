
/*
    Autor: Alex Alves

    Programa para rodar 2 threads e esperar seus terminos
    Para compilar: gcc -o thread2 thread2.c -lpthread
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>   

void *fatorial(void *arg);
void *soma(void *arg);

int main() {
    int res,res2;
    pthread_t thread_1,thread_2;
    int *retorno;
    int *resultado;
    int valor=5;
    int fator=5;
    res = pthread_create(&thread_1, NULL, soma,&valor);
    res2 = pthread_create(&thread_2, NULL,fatorial,&fator);
    if (res != 0 || res2!=0) {
        perror("A thread nao pode ser criada");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(thread_1,(void *)&retorno);
    res2 = pthread_join(thread_2, (void *)&resultado);
    if (res != 0 || res2!=0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
    printf("MAIN()--> O valor da soma foi %d\n",*retorno);
    printf("MAIN()--> O fatorial  eh %d\n", *resultado);
   
    exit(EXIT_SUCCESS);
    free(retorno);
    free(resultado);
}

void *soma(void *arg) {
    int *i;
    i = malloc(sizeof(int));
    i= (int*)arg;
    int somar=0;
    for(int j=1;j<= *i;j++){
        somar = somar +j;
    }
    *i=somar;
    pthread_exit(i);
}

void *fatorial(void *arg) {
    int *aux;
    aux = malloc(sizeof(int));
    aux= (int*)arg;
    int fat=1;
    for(int j= *aux;j>=1;j--){
        fat=fat*j;
    }
    *aux=fat;
    pthread_exit(aux);
}

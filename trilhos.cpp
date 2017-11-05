

/*

    Autor : Alex Alves

    Programa para coordenar ações de treen em trilhos 
    de 1 a 7 onde ambos os treens não podem estar no trilho 3 
    representados aqui por 3 e 8 para saber de onde vem.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void *thread_function(void *arg); // declaração da função a ser executada na thread
int t1=1,t2=5;
pthread_mutex_t work_mutex; /* proteção para: work_area e time_to_exit */

int main() {
    int res,res2,v1=1,v2=2;
    pthread_t thread_1,thread_2;
    void *thread_result;
    
    // Iniciar Multex
    res = pthread_mutex_init(&work_mutex, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }
    
    for(int i=0; i< 20; i++) {
        // Criar thread
        res = pthread_create(&thread_1, NULL, thread_function,&v1);
        res2 = pthread_create(&thread_2, NULL, thread_function,&v2);
        if (res != 0 || res2 != 0) {
            perror("Criação da Thread falhou");
            exit(EXIT_FAILURE);
        }
       
        if(t1>4){
            t1=1;
        }
        if(t2>8){
            t2=5;
        }
        res = pthread_join(thread_1, &thread_result);
        res2 = pthread_join(thread_2, &thread_result);
        if (res != 0 || res2 != 0) {
            perror("Join falhou");
            exit(EXIT_FAILURE);
        }
    }
    
    pthread_mutex_destroy(&work_mutex);  // destruição do multex
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int *L= (int*)arg;
    if(*L==1 && t1!=3){
        printf(" Thread %d na linha %d\n",*L,t1);
        t1++;
    }
    if(*L==2 &&  t2!=8){
        printf(" Thread %d na linha %d\n",*L,t2);
        t2++;
    }
    
    pthread_mutex_lock(&work_mutex);
        // threns 1 ou 2 na linha 3 
        if(*L==1 && t1==3){
            printf(" Thread %d na linha especial - 3\n",*L);
            t1++; 
            sleep(1);
        }
        if(*L==2 && t2==8){
           printf(" Thread %d na linha especial -3\n",*L);
            t2++; 
            sleep(1);
        }
    pthread_mutex_unlock(&work_mutex);
    pthread_exit(0);
}
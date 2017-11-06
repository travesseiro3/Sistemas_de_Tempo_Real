#include <iostream>
#include <pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
using namespace BlackLib;

void *thread_function(void *arg); 
int t1=1,t2=5;
pthread_mutex_t work_mutex; 

//Portas digitais utilizadas no display de 7 segmentos (anodo comum) sem o Dot Point
BlackGPIO a(GPIO_67, output);
BlackGPIO b(GPIO_68, output);
BlackGPIO c(GPIO_66, output);
BlackGPIO d(GPIO_44, output);
BlackGPIO e(GPIO_26, output);
BlackGPIO f(GPIO_69, output);
BlackGPIO g(GPIO_45, output);

float tempo=1,tempo2=1;


void Ligar(int n){
    
    switch(n){

        case 1:
            a.setValue(high); 
            sleeṕ(tempo);
            break;
        case 2:
            b.setValue(high);
            sleeṕ(tempo);
           break;
        
        case 4:     
            f.setValue(high);
            sleeṕ(tempo);
            break;
        case 5:
            c.setValue(high);
            sleeṕ(tempo2);
            break;
        case 6:
            d.setValue(high);
            sleeṕ(tempo2);
            break;
        case 7: 
            e.setValue(high);
            sleeṕ(tempo2);
            break;
        
    }
}

void Desligar(int n){
    switch(n){

        case 0:
            a.setValue(low); 
            b.setValue(low); 
            c.setValue(low); 
            d.setValue(low); 
            e.setValue(low); 
            f.setValue(low); 
            g.setValue(low); 
            break;
        
        case 1:
            a.setValue(low); 
            break;
        case 2:
            b.setValue(low);
           break;
         case 3:     
            g.setValue(low);
            break;
        case 4:     
            f.setValue(low);
            break;
        case 5:
            c.setValue(low);
            break;
        case 6:
            d.setValue(low);
            break;
        case 7: 
            e.setValue(low);
            break;
         case 8:     
            g.setValue(low);
            break;
        
    }
}

int main(){
    //Porta digital utilizada para o PushButton
    BlackGPIO esntrada(GPIO_65, input);
    int val;
    float pot1,pot2;
    //para alimentar os potenciômetros, foi utilizado o VCC_ADC e o GNDA_ADC
    ADC potEsquerdo(AIN3);
    ADC potDireito(AIN5);  
    int res,res2,v1=1,v2=2;
    pthread_t thread_1,thread_2;
    void *thread_result;
    
    // Iniciar Multex
    res = pthread_mutex_init(&work_mutex, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        // lendo o botao
        val = entrada.getNumericValue();
        if(val){
            Desligar(0);
            std::cout<<" Resetando "<< endl;
            slee(1);
        }else {
            //lendo os potenciomentros
            pot1 = potEsquerdo.getFloatValue();
            pot2 = potDireito.getFloatValue();
            if(pot1>0){
                tempo = 1/pot1;
            }
            if(pot2>0){
                tempo2 = 1/pot2;
            }
            
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
    }
    
    pthread_mutex_destroy(&work_mutex);  // destruição do multex
    exit(EXIT_SUCCESS);


   // return 0;
}


void *thread_function(void *arg) {
    int *L= (int*)arg;
    if(*L==1 && t1!=3){
        std::cout<<"Thread 1 na linha  "<< t1 << endl;
        Ligar(t1);
        t1++;
        Desligar(t1);
    }
    if(*L==2 &&  t2!=8){
        std::cout<<"Thread 2 na linha  "<< t2 << endl;
        Ligar(t2);
        t2++;
        Desligar(t2);
    }
    
    pthread_mutex_lock(&work_mutex);
        // threns 1 ou 2 na linha 3 
        if(*L==1 && t1==3){
            std::cout<<"Thread 1 na linha  especial  "<< endl;
            g.setValue(high);          
            t1++; 
            sleep(tempo);
            Desligar(t1);
        }
        if(*L==2 && t2==8){
            std::cout<<"Thread 2 na linha  especial 3 "<< endl;
            g.setValue(high);
            t2++; 
            sleep(tempo2);
            Desligar(t2);
        }
    pthread_mutex_unlock(&work_mutex);
    pthread_exit(0);
}

/*
   Programa para coordenar ações de treen em trilhos 
    de 1 a 7 onde ambos os treens não podem estar no trilho 3 
    representados aqui por 3 e 8 para saber de onde vem.


    ATENÇÃO : A logica do acendimento dos leds esta trocada devido a montagem do circuito. 
    Trocou-se o low pelo high
*/

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

using namespace BlackLib;

//Funcao das threads
void *thread1_function(void *arg);
void *thread2_function(void *arg);
float restrito(int x,float v,float temp,bool valor);
//Meu mutex
pthread_mutex_t my_mutex;
//GPIO outputs
BlackGPIO Led7(GPIO_26, output);
BlackGPIO Led6(GPIO_44, output);
BlackGPIO Led3(GPIO_45, output);
BlackGPIO Led5(GPIO_66, output);
BlackGPIO Led1(GPIO_67, output);
BlackGPIO Led4(GPIO_69, output);
BlackGPIO Led2(GPIO_68, output);
//ADCS
ADC adcLeft(AIN3), adcRight(AIN5);
//auxiliares
float upTrain=1, downTrain=5;

// para resetar
bool reset=false;


// O primeiro parametro eh para saber qual led ta aceso
// O segundo parametro é false se for o trem de baixo e true se for o de cima
int definirProximo(int atual, bool trem){

    int proximo;

    if(trem==true && atual<4){
    proximo = ++atual;
    }
    else if(trem==true && atual==4){
    proximo = 1;
    }
    else if(trem==false && atual<8){
    proximo = ++atual;
    }
    else if(trem==false && atual==8){
    proximo = 5;
    }
    return proximo;
}

int main(int argc, char * argv[]){

   
    //Minha thread
    pthread_t thread1, thread2;
    int res1, res2;
    void *thread_result;
    BlackGPIO botao(GPIO_65, input);
    int val;
    res1 = pthread_mutex_init(&my_mutex, NULL);
    if(res1!=0){
      perror("Iniciacao do Mutex falhou");
      exit(EXIT_FAILURE);
    }
        Led1.setValue(high);
        Led2.setValue(high);
        Led3.setValue(high);
        Led4.setValue(high);
        Led5.setValue(high);
        Led6.setValue(high);
        Led7.setValue(high);
    res1 = pthread_create(&thread1, NULL, thread1_function, NULL);
    res2 = pthread_create(&thread2, NULL, thread2_function, NULL);
    if(res1!=0 || res2!=0){
      perror("Criacao de alguma thread falhou");
      exit(EXIT_FAILURE);
    }
    while(1){
      // Fica lendo o botão
      val=botao.getNumericValue();
      //logica trocada 
      // se o botão for apertado
      if(val){
        std::cout<<" Apertaram o botao -> resetando " << endl;
        reset=true;
        // Apagando todos os leds
        Led1.setValue(high);
        Led2.setValue(high);
        Led3.setValue(high);
        Led4.setValue(high);
        Led5.setValue(high);
        Led6.setValue(high);
        Led7.setValue(high);
        upTrain=1, downTrain=5;
        sleep(2);
        reset=false;
    
      }
      
    }
    res1 = pthread_join(thread1, &thread_result);
    res2 = pthread_join(thread2, &thread_result);
    if(res1!=0 || res2!=0){
      perror("Juncao da Thread falhou");
      exit(EXIT_FAILURE);
    }
    pthread_mutex_destroy(&my_mutex);
    exit(EXIT_SUCCESS);

    return 0;
}

void *thread1_function(void *arg){

    float adcL;
    float tempo=1;
    if(reset){
         std::cout<<" Thread 1 parada " << endl;
    }else{
      while(1){
        std::cout<<"Thread 1 na linha  "<< upTrain << endl;
        adcL = adcLeft.getPercentValue();
        // pra nao dividir por zero
        if(adcL<=0){adcL=10;}
        // pra nao ficar 100 segundos esperando caso adc =1
        if(adcL<20){adcL=20;}
        tempo =100/adcL;
        if(upTrain==1){
          Led1.setValue(low);
          sleep(tempo);
          Led1.setValue(high);
          upTrain = definirProximo(upTrain, true);
        }
        else if(upTrain==2){
          Led2.setValue(low);
          sleep(tempo);
          Led2.setValue(high);
          upTrain = definirProximo(upTrain, true);
        }
        else if(upTrain==3){
          // vai pro mutex
           upTrain= restrito(1,upTrain,tempo,true);
        }
        else if(upTrain==4){
          Led4.setValue(low);
          sleep(tempo);
          Led4.setValue(high);
          upTrain = definirProximo(upTrain, true);
        }

      }

     
    }
    
     pthread_exit(0);
}


void *thread2_function(void *arg){

    float adcR;
    float tempo2=1;
    if(reset){
         std::cout<<" Thread 2 parada " << endl;
    }else{
      while(1){
        std::cout<<"Thread 2 na linha  "<< downTrain << endl;
        adcR = adcRight.getPercentValue();
        // pra nao dividir por zero
        if(adcR<=0){adcR=10;}
        // pra nao ficar 100 segundos esperando caso adc =1
        if(adcR<20){adcR=20; }
        tempo2=100/adcR;
        if(downTrain==5){
          Led5.setValue(low);
          sleep(tempo2);
          Led5.setValue(high);
          downTrain = definirProximo(downTrain, false);
        }
        else if(downTrain==6){
          Led6.setValue(low);
          sleep(tempo2);
          Led6.setValue(high);
          downTrain = definirProximo(downTrain, false);
        }
        else if(downTrain==7){
          Led7.setValue(low);
          sleep(tempo2);
          Led7.setValue(high);
          downTrain = definirProximo(downTrain, false);
        }
        else if(downTrain==8){
           downTrain = restrito(2,downTrain,tempo2,false);
        }

      }
    }
    pthread_exit(0);
}

float restrito(int x,float v,float temp,bool valor){
   pthread_mutex_lock(&my_mutex);
        std::cout<<"Thread " << x << " no trilho eslpecial  " << endl;
        Led3.setValue(low);   
        sleep(temp);
        Led3.setValue(high);
        v= definirProximo(v, valor);

   pthread_mutex_unlock(&my_mutex);
   return v;
}
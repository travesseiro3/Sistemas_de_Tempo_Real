/*
 * Autor: Alex Alves
 * Universidade Federal do Rio Grande do Norte
 */

#include <iostream>
#include <pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> 
#include <stdlib.h>
#include <math.h>
#include <sys/resource.h>
using namespace BlackLib;

void carga(int k)
{
  float f = 0.999999;
  for(int i=0; i<k; i++)
    {
      f = f*f*f*f*f;
      f = 1.56;
        for(int j=0; j<k; j++)
           {
	     f = sin(f)*sin(f)*f*f*f;

            }
    }

}


int main()
{
     BlackGPIO Led2(GPIO_67,output);
     BlackGPIO Led1(GPIO_60,output);  
     ADC pot1(AINx::AIN0);
     ADC pot2(AINx::AIN2);       
     pid_t filho1,filho2 ;
    filho1 =fork();
    if(filho1==-1){
        std::cout << " Nao criou filhho 1 " << endl;
    }else if (filho1 ==0){
        int cont1=0;
        while(1){
          carga(1200);
          if(cont1%2==0){
                Led1.setValue(high);

           }else {
                Led1.setValue(low);
            } 
        
           cont1++; 
        }
    }else {

        filho2 =fork();
        if(filho2==-1){
            std::cout << " Nao criou filhho 1 " << endl;
        }else if (filho2 ==0){
            int cont2=0;
            while(1){
              carga(1200);
              if(cont2%2==0){
                    Led2.setValue(high);

               }else {
                    Led2.setValue(low);
               } 
            
               cont2++; 
            }       
        }else {
	   float  val = pot1.getFloatValue();
	   float val2  = pot2.getFloatValue();
            setpriority(PRIO_PROCESS,0,0);
            usleep(500);
            if(val >1){
                setpriority(PRIO_PROCESS, filho1, 5);
            }else {
                setpriority(PRIO_PROCESS, filho1, 19);
            }

            if(val2 >1){
                setpriority(PRIO_PROCESS, filho2, 5);
            }else {
                setpriority(PRIO_PROCESS, filho2, 19);
            }
        }
    }  
     return 0;
}


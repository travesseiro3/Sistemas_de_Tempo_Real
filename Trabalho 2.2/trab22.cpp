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
    BlackGPIO led2(GPIO_67,output);
    BlackGPIO led1(GPIO_60,output);  
    ADC pot1(AIN0);
    ADC pot2(AIN1);       
    int filho1,filho2 ;
    int cont1=0,cont2=0;
    filho1 =fork();
    if(filho1==-1){
        std::cout << " Nao criou filhho 1 " << endl;
    }else if (filho1 ==0){
        cont1=0;
        while(1){
          carga(1200);
          if(cont1%2==0){
                led1.setValue(high);

           }else {
                led1.setValue(low);
           } 
        
           cont1++; 
        }
    }else {

        filho2 =fork();
        if(filho2==-1){
            std::cout << " Nao criou filhho 1 " << endl;
        }else if (filho2 ==0){
            cont2=0;
            while(1){
              carga(1200);
              if(cont2%2==0){
                    led2.setValue(high);

               }else {
                    led2.setValue(low);
               } 
            
               cont2++; 
            }       
        }else {
        	  float  val = pot1.getFloatValue();
	          float  val2 = pot2.getFloatValue();
        	  if(val==0 && val2==0 ){
        		  led1.setValue(low);
        	    led2.setValue(low);
        	  }else {
          		while(1){       
  	                val = pot1.getFloatValue();
  	                val2  = pot2.getFloatValue();
                    setpriority(PRIO_PROCESS,getpid(),0);
                    usleep(500000);
                    if(val >1){
                        setpriority(PRIO_PROCESS, filho1, 5);
  		              std::cout<<" Potenciometro 1 "<<pot1.getFloatValue() << endl;
                    }else {
                      setpriority(PRIO_PROCESS, filho1, 19);
  		                std::cout<<" Potenciometro 1 "<<pot1.getFloatValue() << endl;

                    }

                    if(val2 >1){
                        setpriority(PRIO_PROCESS, filho2, 5);
                       	std::cout<<" Potenciometro 2 "<<pot2.getFloatValue() << endl;
  		              }else {
    	                    setpriority(PRIO_PROCESS, filho2, 19);
    			                std::cout<<" Potenciometro 2 "<<pot2.getFloatValue() << endl;
    	              }
    	              if(val==0 && val2==0){
      		        		led1.setValue(low);
      		        	  led2.setValue(low);
      		        	   break;
      		        	}
    	          }
	            std::cout<< " Programa finalizado , ate a proxia :) " << endl;
        	}
	         
        }
    }  
     return 0;
}


/*
 * Autor: Alex Alves
 * Universidade Federal do Rio Grande do Norte

   Ascende um Led ao apertar um botão 
 */

#include <iostream>
#include <pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

// Inclua as classes que achar necessario

//using namespace std;
using namespace BlackLib;
//int main(int argc, char * argv[])
int main()
{
   BlackGPIO saida(GPIO_67,output);
   BlackGPIO entrada(GPIO_68,input);
   while(1) {
        //int val = entrada.getValue();
           int val = entrada.getNumericValue();
        if(val){
                saida.setValue(high);
        //      std::cout << "Apertou botao " << endl;

        }else{
                saida.setValue(low);
        //      std::cout << "Soltou botao " << endl;

        }

   }

    
    return 0;
}


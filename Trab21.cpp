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
using namespace BlackLib;

void Tempo(int x, int y)
{
//switch-case para os segundos  (primeiro dígito)
BlackGPIO A(GPIO_66, output);
BlackGPIO B(GPIO_69, output);
BlackGPIO C(GPIO_44, output);
BlackGPIO D(GPIO_45, output);
BlackGPIO E(GPIO_26, output);
BlackGPIO F(GPIO_47, output);
BlackGPIO G(GPIO_46, output);

BlackGPIO a(GPIO_27, output);
BlackGPIO b(GPIO_65, output);
BlackGPIO c(GPIO_61, output);
BlackGPIO d(GPIO_20, output);
BlackGPIO e(GPIO_70, output);
BlackGPIO f(GPIO_72, output);
BlackGPIO g(GPIO_117, output);

BlackGPIO digito1(GPIO_73, output);
BlackGPIO digito2(GPIO_70, output);

 

switch(x){
digito1.setValue(high);
digito2.setValue(low);

    case 0:
        A.setValue(high);
        B.setValue(high);
        C.setValue(high);
        D.setValue(high);
        E.setValue(high);
        F.setValue(high);
        G.setValue(low);
//	sleep(1);

        break;
    case 1:
        A.setValue(low); 
        B.setValue(high);
        C.setValue(high);
        D.setValue(low);
        E.setValue(low);
        F.setValue(low);
        G.setValue(low);
//	sleep(1);
        break;
    case 2:
        A.setValue(high);
        B.setValue(high);
        C.setValue(low);
        D.setValue(high);
        E.setValue(high);
        F.setValue(low);
        G.setValue(high);
//	sleep(1);
 
       break;
    case 3:
        A.setValue(high);
        B.setValue(high);
        C.setValue(high);
        D.setValue(high);
        E.setValue(low);
        F.setValue(low);
        G.setValue(high);
//	sleep(1);

        break;
    case 4:
        A.setValue(low);
        B.setValue(high);
        C.setValue(high);
        D.setValue(low);
        E.setValue(low);
        F.setValue(high);
        G.setValue(high);
//	sleep(1);

        break;
    case 5:
        A.setValue(high);
        B.setValue(low);
        C.setValue(high);
        D.setValue(high);
        E.setValue(low);
        F.setValue(high);
        G.setValue(high);
        break;
    case 6:
        A.setValue(low);
        B.setValue(low);
        C.setValue(high);
        D.setValue(high);
        E.setValue(high);
        F.setValue(high);
        G.setValue(high);
        break;
    case 7:
        A.setValue(high);
        B.setValue(high);
        C.setValue(high);
        D.setValue(low);
        E.setValue(low);
        F.setValue(low);
        G.setValue(low);
        break;
    case 8:
        A.setValue(high);
        B.setValue(high);
        C.setValue(high);
        D.setValue(high);
        E.setValue(high);
        F.setValue(high);
        G.setValue(high);
        break;
    case 9:
        A.setValue(high);
        B.setValue(high);
        C.setValue(high);
        D.setValue(high);
        E.setValue(low);
        F.setValue(high);
        G.setValue(high);
        break;
}

//switch-case para os milisegundos (segundo dígito)
switch(y){
digito1.setValue(low);
digito2.setValue(high);
    case 0:
        a.setValue(high);
        b.setValue(high);
        c.setValue(high);
        d.setValue(high);
        e.setValue(high);
        f.setValue(high);
        g.setValue(low);
//	sleep(1);

        break;
    case 1:
        a.setValue(low);
        b.setValue(high);
        c.setValue(high);
        d.setValue(low);
        e.setValue(low);
        f.setValue(low);
        g.setValue(low);
        break;
    case 2:
        a.setValue(high);
        b.setValue(high);
        c.setValue(low);
        d.setValue(high);
        e.setValue(high);
        f.setValue(low);
        g.setValue(high);
  //      sleep(1);

	 break;
    case 3:
        a.setValue(high);
        b.setValue(high);
        c.setValue(high);
        d.setValue(high);
        e.setValue(low);
        f.setValue(low);
        g.setValue(high);
//	sleep(1);

        break;
    case 4:
        a.setValue(low);
        b.setValue(high);
        c.setValue(high);
        d.setValue(low);
        e.setValue(low);
        f.setValue(high);
        g.setValue(high);
//	sleep(1);

        break;
    case 5:
        a.setValue(high);
        b.setValue(low);
        c.setValue(high);
        d.setValue(high);
        e.setValue(low);
        f.setValue(high);
        g.setValue(high);
        break;
    case 6:
        a.setValue(low);
        b.setValue(low);
        c.setValue(high);
        d.setValue(high);
        e.setValue(high);
        f.setValue(high);
        g.setValue(high);
        break;
    case 7:
        a.setValue(high);
        b.setValue(high);
        c.setValue(high);
        d.setValue(low);
        e.setValue(low);
        f.setValue(low);
        g.setValue(low);
        break;
    case 8:
        a.setValue(high);
        b.setValue(high);
        c.setValue(high);
        d.setValue(high);
        e.setValue(high);
        f.setValue(high);
        g.setValue(high);
        break;
    case 9:
        a.setValue(high);
        b.setValue(high);
        c.setValue(high);
        d.setValue(high);
        e.setValue(low);
        f.setValue(high);
        g.setValue(high);
        break;
 }
}

int main()
{
   srand(time(NULL));
   struct timeval tempo_inicial, tempo_final;
   int val;
   int  seg=0,dsec=0,aux1=0,aux2=0;
   bool inicio= false, botao = false,led=true,contar=true,MostraTempo=false;
   BlackGPIO saida(GPIO_67,output);
   BlackGPIO entrada(GPIO_68,input);
   while(1) {
	val = entrada.getNumericValue();
	//Inicia com led ligado -botao ainda nao apertado
	if(led){
          saida.setValue(high); 
	}
        
        if(val){
		saida.setValue(low);
		led=false;
		inicio = true;
		if(botao){
		   gettimeofday(&tempo_final, NULL); 
	           seg = tempo_final.tv_sec- tempo_inicial.tv_sec;
		   dsec = (tempo_final.tv_usec- tempo_inicial.tv_usec)/100000;
//std::cout << tempo_final.tv_sec << " : " << tempo_inicial.tv_sec << endl;
//std::cout << tempo_final.tv_usec << " : "<<  tempo_inicial.tv_usec << endl;
		   MostraTempo=true;
		   
		   if(dsec<0){
                      dsec  =-1*dsec;
                   } 
 std:: cout << " Tempo de reacao "<< seg << "." << dsec <<"s" << endl;
		   // botao =false;
		   // inicio = false;
                   // sleep(2);
		   // led=true;
		   // contar= true;
		   	
		}		
	}else if (inicio){
		
		if(contar){
		    int r =rand()%3 +1;
                    sleep(r);
                    led = true;
                    saida.setValue(high);
                    gettimeofday(&tempo_inicial, NULL);
		    contar=false;
		    botao = true;
		//	std::cout << " r = " << r << endl;
		}
	}if(MostraTempo){
		Tempo(seg,dsec);
		  botao =false;
                    inicio = false;
                    sleep(2);
                    led=true;
                    contar= true;
		MostraTempo=false;
	}else if(!MostraTempo){
		
		Tempo(aux1,aux2);
		aux1++;
		aux2++;
	//	sleep(1);
		if(aux1>9 ||aux2>9){
		  aux1=0,aux2=0;
		}
	//	std::cout << " aux 1 e 2 "<< aux1 << " " << aux2 << endl; 		
	}else{
		saida.setValue(low);
	//	std::cout << "Soltou botao " << endl;

	}	

   }

    
    return 0;
}


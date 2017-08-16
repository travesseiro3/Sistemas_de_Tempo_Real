
/*
    Programa que o processo gera 2 filhos e cada filho gera dois netos
    Autor : Alex Alves

*/



#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
int main ()
{


    int tempo=10;
    pid_t filho1,filho2 , neto11, neto12,neto21,neto22; 
  
    cout << " Sou o processo pai meu pid eh "<< getpid() << endl; 
    sleep(tempo);
    cout << " Sou o processo pai PID "<< getpid() << " e vou criar o filho 1 " << endl;
    filho1 = fork();
    
    if(filho1==-1) {
        cout << " Nao criou filho 1 " << endl; 
        exit(1);
    } 
    else if(filho1==0) {
        for(int i =0;i<tempo;i++) {

            cout << "Sou filho 1 de PID "<< getpid()<< " Gerado por "<< getppid() << endl; 
        }
        cout << "Sou filho 1 de PID "<< getpid()<< " e vou gerar o neto 1.1 "<< endl; 
        neto11 = fork();
        if(neto11==-1) {
            cout << " Nao criou neto 1.1 " << endl; 
            exit(1);
        } 
        else if(neto11==0) {
            for(int i =0;i<3*tempo;i++) {

                cout << "Sou o neto 1.1 de PID "<< getpid()<< " Gerado por "<< getppid() << endl; 
            }

        } 
        else {
            sleep(tempo);
            cout << "Sou filho 1 de PID "<< getpid()<< " e vou gerar o neto 1.2 "<< endl;   
            neto12 = fork();
            if(neto12==-1) {
                cout << " Nao criou neto 1.2 " << endl; 
                exit(1);
            } 
            else if(neto12==0) {
                for(int i =0;i<3*tempo;i++) {

                    cout << "Sou o neto 1.2 de PID "<< getpid()<< " Gerado por "<< getppid() << endl; 
                }

            }else {
                sleep(tempo);
                cout << " Fim do Filho1 " << endl;

            } 
        }

    } 
    else {
        sleep(tempo);
        cout << " Sou o processo pai PID "<< getpid() << " e vou criar o filho 2 " << endl;
        
        filho2 = fork();
    
        if(filho2==-1) {
            cout << " Nao criou filho 2 " << endl; 
            exit(1);
        } 
        else if(filho2==0) {
            for(int i =0;i<tempo;i++) {

                cout << "Sou filho 2 de PID "<< getpid()<< " Gerado por "<< getppid() << endl; 
            }
            

            cout << "Sou filho 2 de PID "<< getpid()<< " e vou gerar o neto 2.1 "<< endl; 
            neto21 = fork();
            if(neto21==-1) {
                cout << " Nao criou neto 2.1 " << endl; 
                exit(1);
            } 
            else if(neto21==0) {
                for(int i =0;i<3*tempo;i++) {

                    cout << "Sou o neto 2.1 de PID "<< getpid()<< " Gerado por "<< getppid() << endl; 
                }

            } 
            else {
                sleep(tempo);
                cout << "Sou filho 2 de PID "<< getpid()<< " e vou gerar o neto 2.2 "<< endl;   
                neto22 = fork();
                if(neto22==-1) {
                    cout << " Nao criou neto 2.2 " << endl; 
                    exit(1);
                } 
                else if(neto22==0) {
                    for(int i =0;i<3*tempo;i++) {

                        cout << "Sou o neto 2.2 de PID "<< getpid()<< " Gerado por "<< getppid() << endl; 
                    }

                }

                else {
                    sleep(tempo);
                    cout << "Fim do Filho 2 " << endl;
                }

            }


        } 
        else {
            sleep(tempo);
            cout << " Fim do processo pai" << endl;
        }
    }   
   

    return 0;
}

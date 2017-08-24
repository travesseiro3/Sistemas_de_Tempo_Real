
// Autor : Alex Alves

#include <signal.h> // definição dos sinais de interrupções
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // system()
#include <sched.h>
cpu_set_t mask;
void Define_core(int core ) {


    CPU_ZERO(&mask);
    CPU_SET(core, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

}

int  main()
{
  // o processo que vai matar

  int meu_pid;
  int pid_vitima;
  int valor;
  int core;
  meu_pid = getpid();
    
  
 printf( "Eu sou um programa matador de programa meu PID é %d\n", meu_pid );
 printf( "Digite o PID do processo :");
 scanf( "%d", &pid_vitima);


while (1){
    printf("\n Quer falzer o que: Parar o processo(1) , continuar o processo (2) ou matar (3)  \n");
    scanf( "%i", &valor);

    if(valor == 1 ) {
        printf("\n pausando o processo \n");
         kill(pid_vitima, SIGSTOP);
        
    }

    else if(valor == 2) {
        printf("\n continuando o processo \n");
         kill(pid_vitima,SIGCONT);
        
    }
    else if(valor == 3) {
         printf("\n Vou matar o processo %d \n", pid_vitima);
      
        kill(pid_vitima, SIGKILL);
        printf( "\nAgora posso morrer tranquilo.\n");
        break;
        exit(0);
        
    }
    else if(valor == 4) {
        printf("\n Quer que rode em que core da CPU : \n");
        scanf( "%i", &core);
        Define_core(core);
        int z=0;    
        for(int i=0; i<1387634340;i++) {
                z=z+1;
        }
        sleep(5);
    }


}
exit(0);
}







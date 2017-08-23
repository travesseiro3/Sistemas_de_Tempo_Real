

/* Programa destinado para voce escolher o core da CPU
   cujo programa devera ser rodado

    Autor: Alex Alves
*/

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#define _GNU_SOURCE            
#include <sched.h>

using namespace std;

cpu_set_t mask;
void Define_core(int core ) {


    CPU_ZERO(&mask);
    CPU_SET(core, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

}

int main ()
{
int long i;
int j,z;
    while(1){
        j=0,z=0;
           

        Define_core(0);
        for( i=0; i<1387634340;i++) {
                j=j+1;
        }
        cout << getpid() <<" Saiu do laco 1 " <<j<<  endl; 

        Define_core(1);
        for(int i=0; i<1387634340;i++) {
                z=z+1;
        }
        cout << getpid() <<" Saiu do laco 2 " << z<< endl; 
 
   }

    return 0;
}

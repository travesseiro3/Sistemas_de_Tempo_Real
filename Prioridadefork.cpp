#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>     
#include <sys/resource.h>
#include <iostream>
#include <sched.h>

using namespace std;
cpu_set_t mask;
void Define_core(int core ) {


    CPU_ZERO(&mask);
    CPU_SET(core, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

}


int main()
{
    srand(time(NULL));
    pid_t filho1,filho2 ;
    float pot1,pot2;
    filho1 =fork();
    if(filho1==-1){
        cout << " Nao criou filhho 1 " << endl;
    }else if (filho1 ==0){
        Define_core(0);
        for(int j=0; j<2;j++) {
            pot1 =rand()%15;
            setpriority(PRIO_PROCESS, 0, pot1);
            cout << " rand "<< pot1 << endl;
            cout << "Filho1 de pid : " << getpid() << " Com prioridade " << getpriority(PRIO_PROCESS, 0 ) <<endl;
            long int k;
                for( int w=0; w<1387634340;w++) {
                    k=k+1;
                }
        }
    }else {

        filho2 =fork();
        if(filho2==-1){
            cout << " Nao criou filhho 1 " << endl;
        }else if (filho2 ==0){
            Define_core(2);
            for(int i=0; i<2;i++) {
                pot2 =rand()%15;
                setpriority(PRIO_PROCESS, 0, pot2);
                cout << " rand "<< pot2 << endl;
                cout << "Filho 2 de pid : " << getpid() << " Com prioridade " << getpriority(PRIO_PROCESS, 0 ) <<endl;
                long int j;
                for(int wi=0; wi<1387634340;wi++) {
                    j=j+1;
                }
           }        
        }else {
            
            cout << " sou o pai " << endl;
        }
    }

    return 0;
}

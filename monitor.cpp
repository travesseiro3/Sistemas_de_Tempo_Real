#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (){
	printf("Inicio do programa Monitor\n");
	
    while(1) {
      // system("pstree -a| grep prova1");
        system("ps -auf| grep prova1");
        sleep(1);
        system("clear");
    }
	exit (0);
}



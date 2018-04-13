#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>


int main() {

    time_t  now;


    now = time(0);
	
	printf ("Han pasado %d horas desde el 1 de enero de 1970\n", now);

    return 1;
}


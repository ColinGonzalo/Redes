#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>


int main() {
   /* Comprobar la ocurrencia de error y notificarlo con la llamada perror(3) */      
    time_t  now;

    now = time(0);
	
	printf(ctime(&now));
    return 1;
}


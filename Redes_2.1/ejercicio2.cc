#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>




int main() {
   /* Comprobar la ocurrencia de error y notificarlo con la llamada perror(3) */      
if (setuid(0) == -1){ //devuelve -1 si hay error
	//strerror(setuid(0));
	printf("El error es : %s. Code: %d \n" , strerror(errno), errno);
   
}
    return 1;
}


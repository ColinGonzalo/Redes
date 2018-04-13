#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>


int main() {
   /* Comprobar la ocurrencia de error y notificarlo con la llamada perror(3) */      
    time_t  now;
    struct tm *ts;
    char       buf[80];

    /* Obtener la hora actual */
    now = time(0);
	
	printf ("Han pasado %d horas desde el 1 de enero de 1970\n", now);
    /* Formatear e imprimir el tiempo, "ddd yyyy-mm-dd hh:mm:ss zzz" */
   // ts = localtime(&now);
    //strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);
    //printf("%s\n", buf);
    return 1;
}


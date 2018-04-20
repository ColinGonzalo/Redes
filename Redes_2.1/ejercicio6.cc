#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <locale.h>


int main() {
   time_t rawtime;
   struct tm *info;
   char buffer[80];


   time( &rawtime );
   info = localtime( &rawtime );

   strftime(buffer,80,"%Y", info);
   printf("Es el año %s\n", buffer );

   strftime(buffer, 80, "%A, %H:%M", info);
   printf("Hoy es %s\n", buffer);	
	//printf(buffer);

return 0;

}


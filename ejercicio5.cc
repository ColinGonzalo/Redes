#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#define BILLION  1000000000L;



int main() {
   int i = 0;
double accum;
    struct timespec start, stop;

clock_gettime(CLOCK_REALTIME,&start);
	while (i < 10000){
	i++;	
	}
clock_gettime(CLOCK_REALTIME,&stop);

 accum = ( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;
    printf( "%lf\n", accum );
    return 1;
}


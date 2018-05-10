#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

int main (int argc, char **argv)
{

	struct addrinfo hints;	
	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;

	struct addrinfo* res;
	
	int rc = getaddrinfo(argv[1],argv[2], &hints, &res);

	if (rc !=0 ){
		std::cout <<"Error: getaddrinfo() Name or service not known "<< std::endl;
		return -1;
	}

	char host[NI_MAXHOST];
	char server[NI_MAXSERV];
	
	while(res->ai_next != NULL){
	
	int _rc =  getnameinfo(res->ai_addr, res->ai_addrlen,host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST);
		
	if (_rc != 0){
		std::cout <<"Error: getnameinfo()\n ";
		return -1;
	}
		
		std::cout << host << " " << res->ai_family << " " << res->ai_socktype << std::endl;
		res = res->ai_next;
	}
	return 0;
	
}

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <iostream>


int main (int argc, char **argv)
{
	struct addrinfo hints;
	struct addrinfo* res;
	//inicializar socket
	memset((void*) &hints, '\0', sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];

	int rc = getaddrinfo(argv[1],argv[2], &hints, &res);

	if (rc !=0 ){
		std::cout <<"error getaddrinfo(): "<< std::endl;
		return -1;
	}

	int sd = socket (res->ai_family, res->ai_socktype,0);
	
	int conc = connect(sd, res->ai_addr, res->ai_addrlen);
	
	char input[256];
	memset((void*) input, '\0', 256);
	
	
	freeaddrinfo(res);

	struct sockaddr src_addr;
	socklen_t addlen = sizeof(src_addr);

	
	do{
		std::cin.getline(input,256);
		if(strcmp(input, "q") == 0){
			close(sd);
			break;		
		}
		send(sd,input,256,0);
		ssize_t size = recv(sd, input,256,0);	
		std::cout << input << std::endl;

	}while(true);

	return 0;

}

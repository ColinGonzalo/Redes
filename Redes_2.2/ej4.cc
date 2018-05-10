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

	int nm = getnameinfo (res->ai_addr, res->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

	if(nm !=0){
	std::cout << "Error getnameinfo();"<< std::endl;
	return -1;	
	}
	
	
	int sd = socket (res->ai_family, res->ai_socktype,0);
	bind ( sd, res->ai_addr, res->ai_addrlen);
	listen(sd,15);
	freeaddrinfo(res);


	while(true){
		struct sockaddr soc;
		socklen_t size = sizeof(soc);	
		int id = accept(sd, &soc, &size);
		ssize_t recieve ;
int kek = getnameinfo (&soc, size, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
	std::cout << "Conexion establecida con: " << host  << ": " <<  serv << std::endl;
		do{
	
			char buff[256];
			 recieve = recv(id,&buff, 255,0);
	
			if(recieve == 0) break;
			else {
			send(id, &buff, recieve ,0);
}
		}while(recieve != 0);

		std::cout << "Conexión finalizada" << std::endl;
	}

	return 0;

}

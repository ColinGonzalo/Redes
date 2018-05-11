#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <time.h>
int main (int argc, char **argv)
{

	struct addrinfo hints;	
	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	struct addrinfo* res;
	
	int rc = getaddrinfo(argv[1],argv[2], &hints, &res);

	if (rc !=0 ){
		std::cout <<"Error: getaddrinfo() Name or service not known "<< std::endl;
		return -1;
	}

	char host[NI_MAXHOST];
	char server[NI_MAXSERV];
	

	
	int _rc =  getnameinfo(res->ai_addr, res->ai_addrlen,host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST);
		
	if (_rc != 0){
		std::cout <<"Error: getnameinfo()\n ";
		return -1;
	}
		
	int sd = socket ( res->ai_family, res->ai_socktype,0);
	int aux = bind(sd, res->ai_addr, res->ai_addrlen);

	while(true){
		char buff [256];
		struct sockaddr soc;
		socklen_t addrlen = sizeof (soc);
		
		ssize_t size = recvfrom(sd,buff, 255, 0, &soc, &addrlen);
		getnameinfo(&soc, addrlen, host, NI_MAXHOST, server, NI_MAXSERV, 			NI_NUMERICHOST);
		std::cout << size << " bytes de " << host << " " << server << std::endl;

			char buffer[256];
			memset((void*) buffer, '\0',256);
			struct tm* stTime;
			time_t t;
			time (&t);
			stTime = localtime(&t);
		if(buff[0] == 'q'){
			std::cout << "Saliendo..."<< std::endl;
			break;
		}
			
		 else if(buff[0] == 't'){
		
			strftime(buffer,256, "%H:%M:%S", stTime);
			sendto(sd,buffer,256,0,&soc, addrlen);
			
		}
		else if(buff[0] == 'd' ){

			strftime(buffer,256, "%Y-%m-%d", stTime);
			sendto(sd,buffer,256,0,&soc, addrlen);
		}
		else {
			std::cout << "Comando no soportado " << buff[0] << std::endl;
		}

	}

	freeaddrinfo(res);

	return 0;
	
}


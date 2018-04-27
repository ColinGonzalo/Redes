#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <stdio.h>



/*int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
void freeaddrinfo(struct addrinfo *res);

const char *gai_strerror(int errcode);
*/	


	int main(int argc, char* argv[]){

		struct addrinfo hints;
		struct addrinfo* res;
		memset((void*) &hints, '\0', sizeof (struct addrinfo));
		hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
		hints.ai_family = AF_INET;//IPV4
		hints.ai_socktype = SOCK_STREAM;
		int rc = getaddrinfo(argv[1],argv[2], &hints, &res);
		int sd = socket(res->ai_family, res->ai_socktype,0);

		bind (sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);


		listen(sd, 15);
		freeaddrinfo(res);

		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
		struct sockaddr cliente;
		socklen_t cliente_len = sizeof(cliente);



		ssize_t bytes;
		char buffer [256];
		
		while(true){
			bytes = recvfrom(sd, buffer, 80, 0, (struct sockaddr *) &cliente, &cliente_len);
 			buffer[bytes]='\0'; 
    
			getnameinfo((struct sockaddr *) &cliente, cliente_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

			printf("Conexión desde Host:%s Puerto:%s\n",host, serv);
			printf("\tMensaje(%i): %s\n", bytes, buffer);

  			sendto(sd, buffer, bytes, 0, (struct sockaddr *) &cliente, cliente_len);

		}
		return 0;
		}

	

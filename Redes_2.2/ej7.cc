#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

//g++ -o ejc fichero.cc  -lpthread
//ejc localhost 8080
//netstat -uan
//ps -aT     	para ver los threads
//nc -u localhost 8080 			conectarnos al host con udp
class ServerThread{
   public:
 	ServerThread(int s):sd(s){};
	virtual ~ServerThread(){};
	void do_message(){
		
		while (!salir){
			
		char buff[256];
		ssize_t bReciv = recv(sd, &buff, 255, 0 );
		
		if(bReciv == 0){
			salir = true;
			std::cout<< "Saliendo . . .\n";
		}
		else {
			send(sd, &buff, bReciv,0);
			std::cout<< pthread_self() << std::endl;
						

		}
	}
}
   private:
	int sd;
	bool salir;
};
extern "C" void *start_routine (void * _st){
		ServerThread * st = static_cast<ServerThread*>(_st);
		st->do_message();
		delete st;
	
	return 0;

}
int main (int argc, char **argv)
{
	struct addrinfo hints;
	struct addrinfo* res;
	//inicializar socket
	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	char host[NI_MAXHOST];
	char server[NI_MAXSERV];

	int rc = getaddrinfo(argv[1],argv[2], &hints, &res);

	if (rc !=0 ){
		std::cout <<"error getaddrinfo(): " << gai_strerror(rc)<< std::endl;
		return -1;
	}
	int sd = socket (res->ai_family, res->ai_socktype,0);
		bind ( sd, res->ai_addr, res->ai_addrlen);
		listen(sd,15);
		freeaddrinfo(res);
struct sockaddr client;
socklen_t client_len = sizeof(client);
	//inizializar pool de threads
	
			while(true){
				
			int sThread = accept(sd ,(struct sockaddr *) &client, &client_len);
			
			pthread_t tid;
			pthread_attr_t attr;

			ServerThread* st = new ServerThread(sThread);

			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		 	pthread_create(&tid, &attr, start_routine, static_cast<void*>(st));


		}

	// Thread Ppal
	char c;
	std::cin >> c;

	return 0;

}

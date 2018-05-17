#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#define NUM_THREADS 5
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
		while(true){
			char host[NI_MAXHOST];
			char server[NI_MAXSERV];
		char buff [256];
		struct sockaddr soc;
		socklen_t addrlen = sizeof (soc);
		
		ssize_t size = recvfrom(sd,buff, 255, 0, &soc, &addrlen);
		getnameinfo(&soc, addrlen, host, NI_MAXHOST, server, NI_MAXSERV, 			NI_NUMERICHOST);
		std::cout << size << " bytes de " << host << " " << server<<"  Thread: " << pthread_self() << "\n";

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
			sleep(3);

	}


	}
   private:
	int sd;	
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
	hints.ai_socktype = SOCK_DGRAM;

	int rc = getaddrinfo(argv[1],argv[2], &hints, &res);

	if (rc !=0 ){
		std::cout <<"error getaddrinfo(): " << gai_strerror(rc)<< std::endl;
		return -1;
	}
	


	int sd = socket (res->ai_family, res->ai_socktype,0);
		bind ( sd, res->ai_addr, res->ai_addrlen);
		listen(sd,15);
		freeaddrinfo(res);

	//inizializar pool de threads
		for( int i = 0; i <= NUM_THREADS; i++){
			pthread_t tid;
			pthread_attr_t attr;

			ServerThread* st = new ServerThread(sd);

			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		 	pthread_create(&tid, &attr, start_routine, static_cast<void*>(st));


		}

	// Thread Ppal
	char c = 'p';
	while(c != 'q'){
	std::cin >> c;
}
	
	freeaddrinfo(res);
	close(sd);

	return 0;

}

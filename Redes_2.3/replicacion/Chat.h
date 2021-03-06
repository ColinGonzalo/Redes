#include <string>
#include <unistd.h>
#include <string.h>
#include "Serializable.h"
#include "Socket.h"
#include "UDPServer.h"

class ChatMessage: public Serializable
{
public:
    ChatMessage(){};

    ChatMessage(const char * n, const std::string m)
    {
       strncpy(nick, n, 8);
       m.copy(message, 80)
    };

    void to_bin()
    {
      alloc_data(sizeof(char) * 80 + sizeof(int16_t) * 2);
       char* tmp = _data + sizeof(int32_t);
       memcpy(tmp, (void*)nick, 8);
	tmp += 8;
       memcpy(tmp, (void*)message, 80));
	//tmp += 80;
    }

    virtual int from_bin(char * bobj)
    {
        char* tmp = bobj + sizeof(int32_t);
        memcpy(nick, tmp, 8);
	tmp += 8;
	memcpy(message, tmp, 80);
	//tmp+=80;

        return 0;
    }

    char message[80];

    char nick[8];
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/*Ejercicio 7.  Implementar el servidor de chat (ChatServer), cada mensaje recibido se enviará a todos los clientes registrados.*/
class ChatServer : public UDPServer
{
public:
    ChatServer(const char * s, const char * p): UDPServer(s, p){};
    /**
     *  Este método se ejecuta cada vez que se recibe un mensaje
     *    @param buffer, el objeto recibido resultado de Socket::recv. Debe
     *    reconstruirse con Serializable::from_bin
     */
    void do_message(char * buffer)
    {
      ChatMessage msj;
      msj.from_bin(buffer);
    
      for(int i = 0; i < connections.size(); i++){
        //int Socket::send(Serializable * obj, Socket * sock)
        socket.send(&m, connections[i]);
      }
    }
};

/*Ejercicio 8.  Implementar el cliente de chat (ChatClient) que usará dos threads uno para leer de la entrada estándar y enviar los mensajes; y otro que recibirá e imprimirá los mensajes (menos los suyos).*/

class ChatClient
{
public:
    ChatClient(const char * s, const char * p, const char * n):socket(s, p),
        my_nick(n){
          strncpy(my_nick, n, 8);
        };

    void input_thread()
    {
      char m[80];
      ChatMessage* msj;
      while(true){
         std::cin >> m;
         msj = new ChatMessage(my_nick, m);
         msj->to_bin();
         socket.send(m, &socket);
      }
    }

    void net_thread()
    {
      char buff[80];
      ChatMessage* msj;
      while(true){
         //int recv(char * obj)
        socket.recv(buff);
	msj.from_bin(buff);
         
        if(msj.nick != my_nick){
    	   std::cout << "Nick: " << msj.nick <<  " Mensaje: " << msj.message;
    	}  
      }
    }

private:
    char my_nick[8];

    Socket socket;
};


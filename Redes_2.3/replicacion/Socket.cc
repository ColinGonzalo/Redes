#include "Socket.h"
#include "Serializable.h"
#include <stdio.h>
#include <string.h>
inline void error(const string& s){
  throw runtime_error(s);
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Implementación Socket
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/**
 *  Esta función compara dos Socks, realizando la comparación de las structuras
 *  sockaddr: familia (INET), dirección y puerto, ver ip(7) para comparar
 *  estructuras sockaddr_in. Deben comparar el tipo (sin_family), dirección
 *  (sin_addr.s_addr) y puerto (sin_port). La comparación de los campos puede
 *  realizarse con el operador == de los tipos básicos asociados.
 */
bool operator== (const Socket &s1, const Socket &s2)
{
 if(s1.sa.sa_family == AF_INET && s2.sa.sa_family == AF_INET){
	struct sockaddr_in *sock_in1 = (struct sockaddr_in *) s1.sa;
        struct sockaddr_in *sock_in2 = (struct sockaddr_in *) s2.sa;

    return(    sock_in1->sin_family == sock_in2->sin_family &&
		   sock_in1->sin_port == sock_in2->sin_port &&
	sock_in1->sin_addr.s_addr == sock_in2->sin_addr.s_addr );
 }

}

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;
}

// ----------------------------------------------------------------------------
/**
     *  Construye el socket UDP con la dirección y puerto dados. Esta función
     *  usara getaddrinfo para obtener la representación binaria de dirección y
     *  puerto.
     *	int getaddrinfo(const char *nodename, const char *servname,
                const struct addrinfo *hints, struct addrinfo **res);

     *
     *  Además abrirá el canal de comunicación con la llamada socket(2).
     *
     *    @param address cadena que representa la dirección o nombre
     *    @param port cadena que representa el puerto o nombre del servicio
     *
     *  En caso de error lanzar una excepcion std::runtime_error
     */
Socket::Socket(const char * address, const char * port):sd(-1)
{
	struct addrinfo hints, *servinfo;
        int rv;


	memset(&hints, 0, sizeof hints);
     
	hints.ai_family = AF_INET; // use AF_INET6 to force IPv6
	hints.ai_socktype = SOCK_DGRAM; //use SOCK_DGRAM for UDP

	rv = getaddrinfo(address, port, &hints, &servinfo);
	if(rv != 0){
	   error("ERROR en la direccion");
	}
	sa = servinfo->ai_addr;
	sa_len = servinfo->ai_addrlen;

        sd = socket(servinfo->ai_family, servinfo->ai_socktype, 0);

	if(sd == - 1){
	  error("ERROR al crear el socket UDP");	
	}
}

// ----------------------------------------------------------------------------

int Socket::bind()
{
    return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
}

// ----------------------------------------------------------------------------
/**
     *  Envía un mensaje de aplicación definido por un objeto Serializable.
     *  NOTA:La función espera que el objeto esté serializado.
     *
     *    @param obj en el que se enviará por la red
     *
     *    @param sock con la dirección y puerto destino
     *
     *    @return 0 en caso de éxito o -1 si error
     */
int Socket::send(Serializable * obj, Socket * sock)
{
      //Serializamos el objeto;
      obj->to_bin();

     //send() is used for TCP SOCK_STREAM connected sockets, and sendto() is used for UDP SOCK_DGRAM unconnected datagram sockets
     int data = sendto(sock->sd, (void*)obj->data(), obj->size(), 0,(struct sockaddr *)&sock->sa, sock->sa_len);
     
     return data;
}

// ----------------------------------------------------------------------------
 /**
     *  Recibe un mensaje de aplicación
     *
     *    @param obj buffer para recibir los datos de la red. Se usará para la
     *    reconstrucción del objeto mediante Serializable::from_bin del interfaz.
     *    El buffer debe ser de tamaño MAX_MESSAGE_SIZE.
     *
     *    @param sock que identificará al extremo que envía los datos si es
     *    distinto de 0 se creará un objeto Socket con la dirección y puerto.
     *
     *    @return 0 en caso de éxito o -1 si error (cerrar conexión)*/
int Socket::recv(char * buffer, Socket ** sock)
{
 
	char host[NI_MAXHOST];
	char serv [NI_MAXSERV];

        struct sockaddr sock_recv;
	socklen_t sock_recv_len = sizeof(sock_recv);

	buffer = (char*)malloc(MAX_MESSAGE_SIZE); 
        
        ssize_t bytesReceived;

        if(sock != 0){
		bytesReceived = recvfrom(sock->sd, (void*)&buffer, MAX_MESSAGE_SIZE, 0, sock_recv, sock_recv_len);
                sock = new Socket(&sock_recv, sock_recv_len);
	}
 
       return 0;        
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


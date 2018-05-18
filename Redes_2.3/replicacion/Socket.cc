#include "Socket.h"
#include "Serializable.h"

#include <string.h>

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

Socket::Socket(const char * address, const char * port):sd(-1)
{
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
     *    @return 0 en caso de éxito o -1 si error (cerrar conexión)
int Socket::recv(char * buffer, Socket ** sock)
{
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


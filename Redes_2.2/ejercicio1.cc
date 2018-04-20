#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
void freeaddrinfo(struct addrinfo *res);

const char *gai_strerror(int errcode);

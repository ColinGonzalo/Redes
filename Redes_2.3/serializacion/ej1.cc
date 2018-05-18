#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

class Jugador: public Serializable
{
public:
    Jugador(const char * _n, int16_t _x, int16_t _y):x(_x),y(_y)
    {
        strncpy(name, _n, 80);
    };

    virtual ~Jugador(){};

    void to_bin()
    {
       alloc_data(sizeof(char) * 80 + sizeof(int16_t) * 2);
       char* tmp = _data + sizeof(int32_t);
       memcpy(tmp, (void*)name, sizeof(char) * 80);
	tmp +=  sizeof(char) * 80;
       memcpy(tmp, &x, sizeof(int16_t));
	tmp += sizeof(int16_t);
       memcpy(tmp, &y, sizeof(int16_t));
   }

    int from_bin(char * data)
    {
	char* tmp = data + sizeof(int32_t);
        memcpy(name, tmp, 80);
	tmp += 80;
	memcpy(&x, tmp, sizeof(int16_t));
	tmp+=sizeof(int16_t);
	memcpy(&y, tmp, sizeof(int16_t));

	return 0;
    }

public:
    int16_t x;
    int16_t y;
    
    static const size_t MAX_NAME = 80;
    char name[MAX_NAME];

    int input_fd, output_fd;


};

int main(int argc, char **argv)
{
   Jugador player1("Colin", 25, 128);
	Jugador player2("-", 0, 0);
   int fd_opened = open("Archivo.txt", O_RDWR | O_TRUNC | O_CREAT);

   if(fd_opened < 0){
     return 1;
   }

  
   player1.to_bin();

   write(fd_opened, player1.data(), player1.size());
   lseek(fd_opened,0,SEEK_SET);
   char* buf = (char *)malloc(player1.size() + sizeof(int32_t));
   read(fd_opened,buf,player1.size()); 

   close(fd_opened);
   player2.from_bin(buf);

   std::cout << player2.name << " " << player2.x << " " << player2.y << std::endl;
  

   return 0;
  
}

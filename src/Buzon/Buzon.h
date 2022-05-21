#ifndef BUZON_H
#define BUZON_H

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Constante que almacena el de carné.
#define KEY 0xB92211

// Clase encargada de compartir mensajes entre procesos.
class Buzon{
public:
   Buzon();
   void destructor();
   void enviar(char* etiqueta, long mid);
   void recibir(char* etiqueta, int len, long mid);
   
protected:
   int id;
	
   // Estructura que almacena el contenido de los mensajes.   
   struct msgbuf{
      //Ver este enlace para rellenar: https://tldp.org/LDP/lpg/node30.html
      long int message_type;
      char message_text[1024];
   };
};

#endif // BUZON_H

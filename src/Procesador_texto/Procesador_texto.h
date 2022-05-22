#include <string>

#include "Buzon.h"
#include "Semaforo.h"

#define MSG_SIZE 1024

class Procesador_texto {
    public:
        Procesador_texto(const char* archivo);
        ~Procesador_texto();
        void cuentaCaracteresLineas(int start, int finish);
        void recolectarSuma(int cant_procesos);
        void procesarTexto();
        void obtTamanioArchivo();
        void abrir(const char* archivo);         
    private:
        const char* archivo;
        int fd;
        int tamanioArchivo;
        int msgid;
        Semaforo *sem;
        Buzon buzon;
        char *archivo_compartido;
        int cant_caracteres;
        int cant_lineas;
};
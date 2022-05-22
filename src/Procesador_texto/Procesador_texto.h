#include <string>

#include "Buzon.h"
#include "Semaforo.h"

class Procesador_texto {
    public:
        Procesador_texto();
        ~Procesador_texto();
        void cuentaPalabrasLineas();
        void recolectarSuma();
        void procesarTexto();
        int obtTamanioArchivo(int fd);
        int abrir(const char* filepath);
    private:
        const char* archivo;
        Semaforo *sem;
        Buzon buzon;
        char *archivo_compartido;
};
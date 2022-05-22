#include <iostream>

#include "Procesador_texto.h"
#include "Buzon.h"
#include "Semaforo.h"

#define TYPE 1

int main(int argc, char *argv[]) {
    Procesador_texto *procesador;
    // Get file name from args
    if (argc < 2) {
        std::cerr << argv[0] << " [file]" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        procesador = new Procesador_texto(argv[1]);
        procesador->procesarTexto();
    }

    return EXIT_SUCCESS;
}

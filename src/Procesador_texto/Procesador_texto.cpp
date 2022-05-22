
#include <iostream>

#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>

#include "Semaforo.h"
#include "Buzon.h"

// const char* archivo;
// Semaforo *sem;
// Buzon buzon;
// char *archivo_compartido;

Procesador_texto::Procesador_texto(const char* archivo) {
    sem = new Semaforo(1);
    this->archivo = archivo;
}

Procesador_texto::~Procesador_texto() {
    delete sem;
}

int Procesador_texto::abrir(const char* filepath) {
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        std::cerr << "File could not open" << std::endl;
    }
    return fd;
}

int Procesador_texto::obtTamanioArchivo(int fd) {
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        std::cerr << "File is empty" << std::endl;
    }
    return sb.st_size;
}

void Procesador_texto::cuentaPalabrasLineas() {

}

void Procesador_texto::recolectarSuma() {
    
}

void Procesador_texto::procesarTexto() {
    pid_t pid = 0;
    pid_t wait_pid = 0;
    int status = 0;

    // Create 3 child processes
    for(size_t process_index = 0; process_index < 3; process_index++) {
        if ((pid = fork()) == 0) {
            cuentaPalabrasLineas();
            // Exit or parent has to wait process
        }
    }

    // Parent process
    if (pid > 0) {
        recolectarSuma();
    }

    // Wait for processes
    while (wait_pid = wait(&status) > 0);
}

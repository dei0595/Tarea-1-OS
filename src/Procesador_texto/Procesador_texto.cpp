
#include <cmath>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>

#include "Procesador_texto.h"
#include "Semaforo.h"
#include "Buzon.h"

Procesador_texto::Procesador_texto(const char* archivo) {
    sem = new Semaforo(1);
    this->archivo = archivo;
    this->msgid = 1;
}

Procesador_texto::~Procesador_texto() {
    delete sem;
}

void Procesador_texto::abrir(const char* archivo) {
    this->fd = open(archivo, O_RDONLY);
    if (fd == -1) {
        std::cerr << "File could not open" << std::endl;
    }
}

void Procesador_texto::obtTamanioArchivo() {
    struct stat sb;
    if (fstat(this->fd, &sb) == -1) {
        std::cerr << "File is empty" << std::endl;
    }
    this->tamanioArchivo = sb.st_size;
}

void Procesador_texto::cuentaCaracteresLineas(int start, int finish) {
    unsigned int caracteres = 0;
    unsigned int lineas = 0;
    char msg_caracteres [MSG_SIZE];
    char msg_lineas [MSG_SIZE];

    for (off_t caracter = start; caracter < finish; caracter++) {
        if (this->archivo_compartido[caracter] != ' ' && this->archivo_compartido[caracter] != '\n') {
            caracteres++;
            if (static_cast<int>(this->archivo_compartido[caracter]) < 0) {
                caracter++;
            }
            // std::cout << static_cast<int>(this->archivo_compartido[caracter]) << " ";            
        }
        if (this->archivo_compartido[caracter] == '\n' || caracter == this->tamanioArchivo-1) {    
            lineas++;
        }
    }
    
    // String to char* to send through mailbox
    strcpy(msg_caracteres, (std::to_string(caracteres)).c_str());
    strcpy(msg_lineas, (std::to_string(lineas)).c_str());
    
    // Envia a buzon
    this->sem->wait();
    
    buzon.enviar(msg_caracteres, this->msgid);
    buzon.enviar(msg_lineas, this->msgid);
    // std::cout << "Proceso #" << pid << " conto: " << std::endl << "caracteres " << caracteres << std::endl << "lineas " << lineas << std::endl;

    this->sem->signal();
}

void Procesador_texto::recolectarSuma(int cant_procesos) {
    char msg_caracter[MSG_SIZE];
    char msg_linea[MSG_SIZE];

    for (int i = 0; i < cant_procesos ; i++){
        buzon.recibir(msg_caracter, MSG_SIZE, this->msgid); 
        buzon.recibir(msg_linea, MSG_SIZE, this->msgid);    
                  
        // Total sum 
        this->cant_caracteres += atoi(msg_caracter);
        this->cant_lineas += atoi(msg_linea);
    }
    std::cout << "El archivo tiene: " << std::endl;
    std::cout << "Caracteres: " << this->cant_caracteres << std::endl;
    std::cout << "Lineas: " << this->cant_lineas << std::endl;
}


void Procesador_texto::procesarTexto() {
    // Open file
    this->abrir(this->archivo);
    this->obtTamanioArchivo();

    // Init archivo compartido
    this->archivo_compartido = static_cast<char*>(mmap(NULL, this->tamanioArchivo, PROT_READ, MAP_SHARED, this->fd, 0));
    pid_t pid = 0;
    // pid_t wait_pid = 0;
    // int status = 0;
    int cant_procesos = 3;

    // Create 3 child processes
    for(size_t i_proceso = 0; i_proceso < (size_t)cant_procesos; i_proceso++) {
        if ((pid = fork()) == 0) {
            int start = i_proceso*floor(this->tamanioArchivo/cant_procesos) + std::min<int>(i_proceso, this->tamanioArchivo%cant_procesos);
            int finish = (i_proceso+1)*floor(this->tamanioArchivo/cant_procesos) + std::min<int>((i_proceso+1), this->tamanioArchivo%cant_procesos);
            cuentaCaracteresLineas(start, finish);
            exit(1);
        }
    }

    // Parent process
    if (pid > 0) {
        recolectarSuma(cant_procesos);
        munmap(this->archivo_compartido, this->tamanioArchivo);
        close(this->fd);
    }

}

#include "Semaforo.h"

// Método constructor de la clase.
Semaforo::Semaforo(int valorInicial)
{
   // Crear semáforo con semget
}

// Método encargado de eliminar el semáforo.
void Semaforo::destructor()
{
   // Eliminar semáforo con semctl
}

// Método encargado de poner el semáforo en verde.
void Semaforo::signal()
{
   // Utilizar sembuf y semop
}

// Método encargado de esperar que el semáforo esté en verde.
void Semaforo::wait()
{
   // Utilizar sembuf y semop
}

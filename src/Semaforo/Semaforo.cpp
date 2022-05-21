#include "Semaforo.h"

// Método constructor de la clase.
Semaforo::Semaforo(int valorInicial)
{
   // Crear semáforo con semget
   union semun sem;
   sem.val = valorInicial;
   this->id = semget(KEY, 1, IPC_CREAT | 0666);
   if (this->id < 0) {
      fprintf(stderr, "Could not get semaphore\n");
      exit(0);
   }
   if (semctl(this->id, 0, SETVAL, sem) < 0) {
      fprintf(stderr, "Could not create sempahore\n")
   }
}

// Método encargado de eliminar el semáforo.
void Semaforo::destructor()
{
   // Eliminar semáforo con semctl
   semctl(id, 0, IPC_RMID);
}

// Método encargado de poner el semáforo en verde.
void Semaforo::signal()
{
   // Utilizar sembuf y semop
   struct sembuf ops[1];
   int val;
   ops[0].sem_num = 0;
   ops[0].sem_op = 1;
   ops[0].sem_flg = 0;

   val = semop(this->id, ops, 1);
   if (val != 0) {
      fprintf(stderr, "Could not init semaphore\n")
   }
}

// Método encargado de esperar que el semáforo esté en verde.
void Semaforo::wait()
{
   // Utilizar sembuf y semop
   struct ops[1];
   int val;
   ops[0].sem_num = 0;
   ops[0].sem_op = -1;
   ops[0].sem_flg = 0;

   val = semop(this->id, ops, 1);
   if (val == 0) {

   } else {
      
   }
}

#include "Buzon.h"

// Constructor de la clase.
Buzon::Buzon()
{
    // Crear el Buzón con msgget
    this->id = msgget(KEY, 0666 | IPC_CREAT);
}

// Método encargado de eliminar el buzón.
void Buzon::destructor()
{
    struct msqid_ds str;
    // Eliminar el buzón con msgctl
    msgctl(id, IPC_RMID, &str);
}

// Método encargado de enviar un mensaje al buzón.
void Buzon::enviar(char* etiqueta, long mid)
{
    // Inicializar el contenido del mensaje con msgbuf
    struct msgbuf data;
    data.message_type = mid;
    
    strcpy(data.message_text, etiqueta);

    // Enviar el mensaje con msgsnd
    // int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    if (msgsnd(this->id, (void*)&data, sizeof(data.message_text), 0) == -1) {
        std::cout << "Message couldn't be sent..." << std::endl;
    } 

}

// Método encargado de recibir un mensaje.
void Buzon::recibir(char* etiqueta, int len, long mid)
{
    // Inicializar el contenido del mensaje con msgbuf
    struct msgbuf data;

    // Recibir el mensaje con msgrcv
    // ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
    msgrcv(this->id, (void*)&data, len, mid, 0);
    std::cout << "Data received: " << data.message_text << std::endl;
    // Sacar el mensaje del buzón. Sugerencia: strcpy
    strcpy(etiqueta, data.message_text);
}

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Buzon.h"

using namespace std;

#define TYPE 1

int main()
{
    Buzon b;
    pid_t id = fork(); // crea un proceso
    if(id < 0){
        cout << "Error en el fork" <<endl;
    }

    if(id == 0){ // child process
        sleep(2);
        b.enviar("Hola proceso padre, soy tu hijo");
        // struct msgbuf _mb;
        // _mb.mtype = TYPE;
        // string msg = "hello!";
        // strcpy(_mb.mtext, msg.c_str());
        // if(msgsnd(msgid, (void*)&_mb, sizeof(_mb.mtext), 0) < 0){
        //     cout << "msgsnd error !!" <<endl;
        // }
    }
    else{ // parent process
        if (fork() == 0) { // Third child process
            b.enviar("Hola proceso padre, soy tu segundo hijo ");
        } else {
            b.recibir();
            b.recibir();
        }
        
        // struct msgbuf _mb;
        // if (msgrcv(msgid, &_mb, sizeof(_mb.mtext), TYPE, 0)< 0){
        //     cout << "msgrcv error !!" <<endl;
        // }
        // char buf[100];
        // strcpy(buf,_mb.mtext);
        // cout << "father recv:" << buf <<endl;
    }
    if (waitpid(id,NULL,0) != -1 ) {
        std::cout << "Process: " << getpid() << " Terminated" << std::endl;
    }
    
    return 0;
}
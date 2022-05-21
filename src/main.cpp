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
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <atomic>
#include <cstring>
#include <regex>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include "Semaforo.h"
#include "Buzon.h"
#include <iostream>
// #include "Buzon.h"
// #include "Semaforo.h"

using namespace std;

#define TYPE 1

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    Semaforo sem;
    char *addr;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t length;
    // ssize_t s;

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "%s file offset [length]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    offset = atoi(argv[2]);
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
        /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size) {
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 4) {
        length = atoi(argv[3]);
        if (offset + length > sb.st_size)
            length = sb.st_size - offset;
                /* Can't display bytes past end of file */

    } else {    /* No length arg ==> display to end of file */
        length = sb.st_size - offset;
    }

    addr = static_cast<char*>(mmap(0, sb.st_size , PROT_READ, MAP_SHARED, fd, 0));

    if (addr == MAP_FAILED)
        handle_error("mmap");

    for (off_t i = 0; i < sb.st_size; i++)
    {
        if (addr[i] == '\n')
            printf("Found character %c at %ji\n", addr[i], (intmax_t)i);
    }
    munmap(addr, length + offset - pa_offset);
    close(fd);

    exit(EXIT_SUCCESS);
}

// int main(int argc, char* argv[]) {
//     const char *filepath = argv[1];
//     int fd = open(filepath, O_RDONLY, (mode_t)0600);
//     if (fd == -1) {
//         fprintf(stderr, "Could not open file\n");
//         exit(EXIT_FAILURE);
//     } 
//     // Get the file size
//     struct stat fileInfo = {0};
//     if (fstat(fd, &fileInfo) == -1) {
//         fprintf(stderr, "Error getting file size\n");
//     }
//     // File is empty
//     if (fileInfo.st_size == 0) {
//         fprintf(stderr, "File is empty, nothing to do\n");
//     }
//     printf("File size is %ji\n", (intmax_t)fileInfo.st_size);

//     // Load shared memory
//     char *map = mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
    
//     // Read
//     for (off_t i = 0; i < fileInfo.st_size; i++)
//     {
//         printf("Found character %c at %ji\n", map[i], (intmax_t)i);
//     }

//     // Free memory
//     if (munmap(map, fileInfo.st_size) == -1)
//     {
//         close(fd);
//         perror("Error un-mmapping the file");
//         exit(EXIT_FAILURE);
//     }

//     // Close file
//     close(fd);
//     return 0;
// }

// int main()
// {
    // Buzon b;
    // pid_t id = fork(); // crea un proceso
    // if(id < 0){
    //     cout << "Error en el fork" <<endl;
    // }

    // if(id == 0){ // child process
    //     sleep(2);
    //     b.enviar("Hola proceso padre, soy tu hijo");
    //     // struct msgbuf _mb;
    //     // _mb.mtype = TYPE;
    //     // string msg = "hello!";
    //     // strcpy(_mb.mtext, msg.c_str());
    //     // if(msgsnd(msgid, (void*)&_mb, sizeof(_mb.mtext), 0) < 0){
    //     //     cout << "msgsnd error !!" <<endl;
    //     // }
    // }
    // else{ // parent process
    //     if (fork() == 0) { // Third child process
    //         b.enviar("Hola proceso padre, soy tu segundo hijo ");
    //     } else {
    //         b.recibir();
    //         b.recibir();
    //     }
        
    //     // struct msgbuf _mb;
    //     // if (msgrcv(msgid, &_mb, sizeof(_mb.mtext), TYPE, 0)< 0){
    //     //     cout << "msgrcv error !!" <<endl;
    //     // }
    //     // char buf[100];
    //     // strcpy(buf,_mb.mtext);
    //     // cout << "father recv:" << buf <<endl;
    // }
    // if (waitpid(id,NULL,0) != -1 ) {
    //     std::cout << "Process: " << getpid() << " Terminated" << std::endl;
    // }
    
//     return 0;
// }


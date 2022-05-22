#include <atomic>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include "Buzon.h"
#include "Semaforo.h"

#define TYPE 1



int main(int argc, char *argv[])
{
    char *addr;
    int fd = openFile(argv[1]);
    struct stat sb;
    off_t offset, pa_offset;
    size_t length;
    ssize_t s;
    size_t fileSize = getFileSize(fd, sb);
    double segmentSize;
    // Get file name from args
    if (argc < 2) {
        std::cerr << argv[0] << " [file]" << std::endl;
        exit(EXIT_FAILURE);
    }
    addr = static_cast<char*>(mmap(NULL, sb.st_size, PROT_READ,
                MAP_SHARED, fd, 0));
    segmentSize = fileSize / (double)3;
    double floor = floor(segmentSize);
    int ceil = segmentSize - floor*2;
    std::vector<int> seg = {floor, ceil};
    std::cout << seg[0] << std::endl;
    std::cout << seg[1] << std::endl;

    for (off_t i = offset; i < offset + length; i++)
    {
        printf("Found character %c at %ji\n", addr[offset], (intmax_t)i);
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


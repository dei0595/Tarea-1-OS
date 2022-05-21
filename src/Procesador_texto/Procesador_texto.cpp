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

class Procesador_texto {
    public:
        Procesador_texto();
        ~Procesador_texto();
    private:
        size_t num_procesos;
        
};

// int main(int argc, char* argv[]) {
//     const char *filepath = argv[1];
//     int fd = open(filepath, O_RDONLY, (mode_t)0600);
//     if (fd == -1) {
//         fprintf(stderr, "Could not open file\n");
//         exit(EXIT_FAILURE);
//     } 
//     // Get the file size
//     struct stat fileInfo = {0}
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
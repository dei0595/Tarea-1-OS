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

#include "Semaforo.h"
#include "Buzon.h"

class Procesador_texto {
    public:
        Procesador_texto();
        ~Procesador_texto();
    private:
        size_t num_procesos;
        std::map<string>
};
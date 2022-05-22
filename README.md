# Tarea Programada #1: Comunicación entre varios procesos utilizando buzones y memoria compartida

## ¿Es posible la comunicación de procesos utilizando solamente una región de memoria compartida?

Sí, es posible. Debido a que la memoria compartida es una forma de comunicación entre procesos implícita. Esto quiere decir que los procesos no se envían y reciben datos directamente, sino más bien que los procesos pueden acceder a una misma región de memoria, esto es posible porque se crea un segmento fuera del espacio de direccionamiento de un proceso y cada proceso que necesite informacion de la region de memoria, la va a incluir como parte de su espacio de direccionamiento virtual. Entonces un proceso P1 podria escribir en una sección y el proceso P2 podría leer esa misma sección y viceversa, esto porque estan compartiendo un segmento de memoria.

El inconveniente con la memoria compartida es que se tiene que crear mecanismos de sincronización para evitar errores de control de concurrencia.

## Integrantes

- Deivy Alvarado B30286

- Sam Cheang B92211

## Para compilar y ejecutar

- Compilar <make>
  
- Ejecutar <bin/Tarea-1-OS nombre_archivo>

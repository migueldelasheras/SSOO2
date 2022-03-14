/*
    Código correspondiente al proceso pd en el que se eliminará todo el contenido creado en los otros 
    procesos.

    Código realizado por: MIGUEL DE LAS HERAS FUENTES
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    
    FILE *log = fopen("log.txt","w");
    fputs("Se ha producido una interrupcion voluntaria ordenada por el usuario\n",log);
    fclose(log);

    char *const arg_list[] = {"/bin/bash","-c","rm -r estudiantes",NULL};
    execve("/bin/bash",arg_list,NULL);
    
}
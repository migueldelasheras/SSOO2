/*
    Archivo correspondiente al proceso demonio que se ejecutará en segundo plano y realizará una
    copia de seguridad de todos los archivos generados. La primera copia se realizará al principio
    y cada 60 segundos se repetirá el proceso.

    Código realizado por: MIGUEL DE LAS HERAS FUENTES
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

void ManejadorAlarm(int sig);

int main(){

    signal(SIGALRM,ManejadorAlarm);
    //Se lanza la señal para realizar la primera copia
    alarm(1);
    pause();

    //Se lanzará la señal alarm cada 60 segundos para realizar la copia de seguridad de los archivos
    while (1)
    {
        alarm(60);
        pause();
    }
    

}

void ManejadorAlarm(int sig){
    
    //printf("copia realizada\n");

    pid_t pid = fork();
    if (pid==-1)
    {
        fprintf(stderr,"Error en el proceso demonio\n");
    }else if (pid==0)
    {
        mkdir("copia",S_IRWXU);
        char *const arg_list[] = {"/bin/bash","-c","cp -r estudiantes copia & cp log.txt copia", NULL};
        execve("/bin/bash",arg_list,NULL);
        fprintf(stderr,"Error al hacer la copia de seguridad\n");
    }
    
    
}
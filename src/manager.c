/*
    Código correspondiente al proceso manager en el que se realizarán las llamadas a los procesos pa,
    pb y pc y se controlarán señales de terminación como "SIGINT"(Ctrl+C) llamando al proceso pd.
    
    Código realizado por: MIGUEL DE LAS HERAS FUENTES

*/

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LECTURA 0
#define ESCRITURA 1

pid_t pid1,pid2,pid3; //PROCESOS A,B Y C

void manejadorInt(int sig);
void lanzadorDemon();

int main(){

    //Manejador de la señal SIGINT
    signal(SIGINT,manejadorInt);

    //Se lanza el proceso demonio
    lanzadorDemon();

    //Creación del fichero log.txt para el seguimiento de la ejecución
    FILE *log = fopen("log.txt","wr");
    fputs("******** Log del sistema ********\n",log);

    char *const arg_list[] = {NULL};

    //Creación del proceso pa
    pid1 = fork();

    switch (pid1)
    {
    case -1:
        
        fprintf(stderr,"No se ha podido crear el proceso PA\n");
        exit(EXIT_FAILURE);

    case 0:
        
        execve("./pa",arg_list,NULL);
        fprintf(stderr,"Se ha producido un error en el proceso PA\n");
        exit(EXIT_FAILURE);
    
    default:
        
        wait(NULL);
        fputs("Creación de directorios finalizada.\n",log);
        break;
    
    }
    
    //Creación de la tuberia Pc -> manager
    int tuberiaPcManager[2]; 
    pipe(tuberiaPcManager);
    char wr_tuberiaPC[256];
    sprintf(wr_tuberiaPC,"%d",tuberiaPcManager[ESCRITURA]); //descriptor del canal escritura PC

    //Creación de los procesos hijos Pb(i=0) y Pc(i=1)
    for (int i = 0; i < 2; i++)
    {
        pid_t pid = fork();

        if (pid==-1)
        {
            fprintf(stderr,"Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        }
        if (pid==0)
        {
            if (i==0)
            {
                execv("./pb",arg_list);
                fprintf(stderr,"Se ha producido un error en el proceso pb");
                exit(EXIT_FAILURE);

            }else{

                execl("./pc",wr_tuberiaPC,NULL);
                fprintf(stderr,"Se ha producido un error en el proceso pc");
                exit(EXIT_FAILURE);

            }
            
        }

        //Almacenamiento de los pids de los procesos hijos(Pb y Pc) creados
        if (i==0)
        {
            pid2 = pid;
        }else{
            pid3= pid;
        }
         
    }
    
    //Se espera a la finalización del proceso Pb
    waitpid(pid2,NULL,0);
    fputs("Copia de modelos de examen, finalizada.\n",log);

    //Lectura de la tuberia Pc-> manager para obtener la nota media
    char buffer[256];
    close(tuberiaPcManager[ESCRITURA]);
    read(tuberiaPcManager[LECTURA],buffer,sizeof(buffer));

    fputs("Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n",log);
    fputs("La nota media de la clase es: ",log);
    fputs(buffer, log);
    fputs("\nFIN DEL PROGRAMA",log);
    fclose(log);
    
}

//Manejador de la señal "SIGINT"(Ctrl+C)
void manejadorInt(int sig){

    printf("Finalizando los procesos creados...\n");
    kill(pid1,SIGKILL);
    kill(pid2,SIGKILL);
    kill(pid3,SIGKILL);
    
    char *const arg_list[] = {NULL};
    pid_t pid = fork();

    if (pid==-1)
    {
        fprintf(stderr,"No se ha podido crear el proceso de finalización pd");
        exit(EXIT_FAILURE);
    }
    if (pid==0)
    {

        execve("./pd",arg_list,NULL);
        fprintf(stderr,"Se ha producido un error en el proceso Pd");
        exit(EXIT_FAILURE);
    }

}

//Función que lanzará el proceso Demonio en segundo plano al comienzo de la ejecución
void lanzadorDemon(){

    pid_t pid = fork();
    char *const arg_list[] = {NULL}; 

    if (pid==-1)
    {
        fprintf(stderr,"No se ha podido crear el proceso demonio");
        exit(EXIT_FAILURE);
    }
    if (pid==0)
    {

        execve("./demonio",arg_list,NULL);
        fprintf(stderr,"Se ha producido un error en el proceso Pd");
        exit(EXIT_FAILURE);
    }
    
}


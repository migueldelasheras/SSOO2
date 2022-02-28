#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LECTURA 0
#define ESCRITURA 1

void manejador(int sig);

int main(){

    signal(SIGINT,manejador);

    FILE* log= fopen("log.txt","wr");
    fputs("******** Log del sistema ********\n",log);

    //creacion del proceso pa
    pid_t pid1 = fork();
    char *const arg_list[] = {NULL}; //mirar lo de const

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
        
        waitpid(pid1,NULL,0);
        fputs("Creación de directorios finalizada.\n",log);
        break;
    
    }

    //sleep(10);
    
    int pClass; //tipo de proceso creado (B o C)

    int tuberiaPcManager[2]; //tuberia PC->manager
    pipe(tuberiaPcManager);
    char wr_tuberiaPC[256];

    sprintf(wr_tuberiaPC,"%d",tuberiaPcManager[ESCRITURA]); //descriptor del canal escritura PC

    pid_t pid;
    pid_t pid2,pid3;

    for (int i = 0; i < 2; i++) //creacion de los procesos B y C
    {
        pid = fork();
        if (pid==0){
            if(i==0)
                pClass=0; //el 0 corresponde al proceso b
            else 
                pClass=1; //el 1 corresponde al proceso c
            break;
        }
        
    }

    switch (pid)
    {
    case -1:

        fprintf(stderr,"No se ha podido crear el proceso hijo");
        exit(EXIT_FAILURE);

    case 0:
        
        if (pClass==0)
        {
            printf("proceso b"); //por qué no se ejecuta nunca?
            execv("./pb",arg_list);
            fprintf(stderr,"Se ha producido un error en el proceso Pb");
            exit(EXIT_FAILURE);

        }else{

            close(tuberiaPcManager[LECTURA]);
            execl("./pc",wr_tuberiaPC,NULL);
            fprintf(stderr,"Se ha producido un error en el proceso Pc");
            exit(EXIT_FAILURE);

        }

    default:

        //primero debemos hacer un waitpid(PA)
        fputs("Copia de modelos de examen, finalizada.\n",log);

        char buffer[256];
        close(tuberiaPcManager[ESCRITURA]);
        read(tuberiaPcManager[LECTURA],buffer,sizeof(buffer));
        
        fputs("Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n",log);
        fputs("La nota media de la clase es: ",log);
        fputs(buffer, log);
        fputs("\nFIN DEL PROGRAMA",log);
        
        break;
    }

}

void manejador(int sig){
    printf("se ha parado el programa\n");
}
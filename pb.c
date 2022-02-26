#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define Max 8192
#define MODA "A"
#define MODB "B"
#define MODC "C"


int copiar(char *origenS, char *destinoS);


int main(){

    char *filename = "estudiantes.txt";
    FILE *fp= fopen(filename,"r");

    if (fp==NULL){
        printf("No se ha podido abrir el archivo estudiantes.txt");
        exit(EXIT_FAILURE);
    }

    char* directorio = "estudiantes/";
    char* alumno;
    char* modelo;
    char* destinoStr;

    const unsigned MAX_LENGTH = 256;
    char line[MAX_LENGTH]; //cadena que contiene la linea del archivo estudiantes.txt
    char *token;

    while (fgets(line, MAX_LENGTH, fp)){

        //directorio="estudiantes/";
        
        
        token= strtok(line," "); //dni del estudiante
        alumno = token;
        token= strtok(NULL," "); //modelo de examen del estudiante
        modelo = token;

        strcat(strcpy(destinoStr, directorio), alumno); //destino == estudiantes/0572938
        strcat(destinoStr, "/"); //destino == estudiantes/0572938/
        strcat(destinoStr, modelo); //destino == estudiantes/0572938/A
        strcat(destinoStr, ".pdf"); //destino == estudiantes/0572938/A.pdf


        //printf("%s <-- ",destinoStr);

        char* origenStr;
        //printf("-----%s------",modelo);
        
        
        if(strcmp(modelo,MODA)==0){
            origenStr = "examenes/A.pdf";
            //printf("Se ha elegido A");
            
        }
        if(strcmp(modelo,MODB)==0)
        {
            origenStr = "examenes/B.pdf";
            //printf("Se ha elegido B");

            
        }
        if(strcmp(modelo,MODC)==0){
            origenStr = "examenes/C.pdf";
            //printf("Se ha elegido C");

        }
        

        
        //printf("%s\n",origenStr);
        copiar(origenStr,destinoStr);
       
    }

}
int copiar(char *origenS, char *destinoS){
    int sfd, dfd, ret_in, ret_out;
    char buff[Max];

    if ( (sfd = open(origenS, O_RDONLY)) == -1 )
    {
        printf("Error while reading %s\n", origenS);
        perror(origenS);
        exit(1);
    }

    if ( (dfd = creat(destinoS, 0644)) == -1 )
    {
        printf("Error while creating %s\n", destinoS);
        perror(destinoS);
        exit(1);
    }

    while( (ret_in = read(sfd, &buff, Max)) > 0 )
    {
        ret_out = write (dfd, &buff, ret_in);

        if (ret_out != ret_in)
        {
            printf("write error to %s", destinoS);
            perror(destinoS);
            exit(1);
        }

        if (ret_in == -1)
        {
            printf("read error from %s", origenS);
            perror(origenS);
            exit(1);
        }
    }

    close(sfd);
    close(dfd);

    return 1;

}
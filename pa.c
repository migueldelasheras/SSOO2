#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>


int main(){

    char *filename = "estudiantes.txt";
    FILE *fp= fopen(filename,"r");

    if (fp==NULL){
        printf("No se ha podido abrir el archivo estudiantes.txt");
        exit(EXIT_FAILURE);
    }

    char* directorio;
    char* alumno;

    const unsigned MAX_LENGTH = 256;
    char line[MAX_LENGTH];
    char *token;

    while (fgets(line, MAX_LENGTH, fp)){

        directorio="estudiantes/";
        
        token= strtok(line," ");
        
        strcat(strcpy(alumno, directorio), token);

        mkdir(alumno,S_IRWXU);
    }
    printf("Creación de directorios finalizada\n");
    

    
}
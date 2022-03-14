/*
    Código correspondiente al proceso Pa que consistirá en la creación de los directorios de cada 
    estudiante.

    Código realizado por: MIGUEL DE LAS HERAS FUENTES
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


int main(){

    //Se abre el archivo estudiantes.txt para su lectura
    char *filename = "estudiantes.txt";
    FILE *fp= fopen(filename,"r");

    if (fp==NULL){
        printf("No se ha podido abrir el archivo estudiantes.txt");
        exit(EXIT_FAILURE);
    }

    //directorio general donde estarán todos los directorios de los estudiantes
    char* directorio="estudiantes/";
    mkdir(directorio,S_IRWXU);
    //DNI del alumno y por tanto nombre del directorio de dicho alumno
    char* dirAlumno; 

    const unsigned MAX_LENGTH = 256;
    char line[MAX_LENGTH];
    char *token;
    
    //lectura del fichero estudiantes.txt
    while (fgets(line, MAX_LENGTH, fp)){

        //directorio="estudiantes/";
        token= strtok(line," ");

        strcat(strcpy(dirAlumno, directorio), token);

        mkdir(dirAlumno,S_IRWXU);
    }
    fclose(fp);
    
}
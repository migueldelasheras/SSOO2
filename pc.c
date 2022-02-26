#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define totalAlum 15

int calcularNota(int nota);

int crearFichero(char* fd, int minima);

int main(int argc,char *argv[]){

    char *filename = "estudiantes.txt";
    FILE *fp= fopen(filename,"r");

    if (fp==NULL){
        printf("No se ha podido abrir el archivo estudiantes.txt");
        exit(EXIT_FAILURE);
    }

    const char directorio[] = "estudiantes/";
    char* alumno;
    char* modelo;
    char* nota;
    char* destinoStr;
    int media;

    const unsigned MAX_LENGTH = 256;
    char line[MAX_LENGTH]; //cadena que contiene la linea del archivo estudiantes.txt
    char *token;

    while (fgets(line, MAX_LENGTH, fp)){
        
        token= strtok(line," "); //dni del estudiante
        alumno = token;
        token= strtok(NULL," "); //modelo de examen del estudiante
        modelo = token;
        token = strtok(NULL," "); //nota del estudiante
        nota = token; 

        strcat(strcpy(destinoStr, directorio), alumno); //destino == estudiantes/0572938
        strcat(destinoStr, "/nota.txt"); //destino == estudiantes/0572938/

        
        media += atoi(nota);
        crearFichero(destinoStr,calcularNota(atoi(nota)));

    }

    //char mensaje[] = "La nota media de la clase es: ";
    char med[2];
    media = media/15;
    sprintf(med,"%d",media);
    //strcat(mensaje,med);

    //printf("%s",mensaje);

    write(atoi(argv[0]),med,strlen(med)+1);

}

int calcularNota(int nota){
    int minima= 10 - nota;
    return minima;
}

int crearFichero(char* fd, int minima){

   FILE* fichero;
   char cadena[]= "La nota que debes obtener en este nuevo examen para superar la prueba es: ";
   char nota[2];

   sprintf(nota, "%d", minima);
   strcat(cadena,nota);
   //printf("%s\n",cadena);

   fichero = fopen(fd,"w");
   fputs(cadena, fichero);

}
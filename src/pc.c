/*
    Código correspondiente al proceso pc en el que se calculará la nota mínima que necesitan los 
    alumnos para superar la prueba. Se creará un fichero en el que se escribirá esta nota. 
    Por último, se enviará la nota media de los alumnos al proceso manager mediante una tubería.

    Código realizado por: MIGUEL DE LAS HERAS FUENTES

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TOTALALUM 15

int calcularNota(int nota);
int crearFichero(char* fd, int minima);

int main(int argc,char *argv[]){

    //Se abre el archivo estudiantes.txt para su lectura
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
    int media; //variable donde almacenaremos la media de los alumnos

    const unsigned MAX_LENGTH = 256;
    char line[MAX_LENGTH]; //cadena que contiene la linea del archivo estudiantes.txt
    char *token;

    while (fgets(line, MAX_LENGTH, fp)){
        
        token= strtok(line," ");
        alumno = token;
        token= strtok(NULL," ");
        modelo = token;
        token = strtok(NULL," ");
        nota = token; 

        strcat(strcpy(destinoStr, directorio), alumno); //destino == estudiantes/0572938
        strcat(destinoStr, "/nota.txt"); //destino == estudiantes/0572938/

        media += atoi(nota);
        crearFichero(destinoStr,calcularNota(atoi(nota)));

    }

    char med[2];
    media = media/TOTALALUM;
    sprintf(med,"%d",media);
    
    write(atoi(argv[0]),med,strlen(med)+1);

}

//función que calcula la nota que un alumno necesita para aprobar la prueba
int calcularNota(int nota){
    int minima= 10 - nota;
    return minima;
}

//Función que crea el fichero que contiene la nota calculada en la función calcularNota
int crearFichero(char* fd, int minima){

   FILE* fichero = fopen(fd,"w");
   char cadena[]= "La nota que debes obtener en este nuevo examen para superar la prueba es: ";
   char nota[2];

   sprintf(nota, "%d", minima);
   strcat(cadena,nota);

   fputs(cadena, fichero);

}
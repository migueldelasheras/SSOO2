/* 
    Código correspondiente al proceso pb en el que se copiará el modelo de examen que le corresponda 
    a cada alumno es su directorio.

    Código realizado por: MIGUEL DE LAS HERAS FUENTES
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MODA "A"
#define MODB "B"
#define MODC "C"

int main(){

    //Se abre el archivo estudiantes.txt para su lectura
    char *filename = "estudiantes.txt";
    FILE *fp= fopen(filename,"r");

    if (fp==NULL){
        printf("No se ha podido abrir el archivo estudiantes.txt");
        exit(EXIT_FAILURE);
    }

    char* directorio = "estudiantes/";
    char* alumno;
    //modelo de examen que le corresponde al alumno(A,B o C)
    char* modelo; 
    //cadena donde se almacenará la dirección donde se copiará el modelo de examen
    char* destinoStr;

    const unsigned MAX_LENGTH = 256;
    char line[MAX_LENGTH]; //cadena que contiene la linea del archivo estudiantes.txt
    char *token;

    while (fgets(line, MAX_LENGTH, fp)){

        token= strtok(line," "); 
        alumno = token;
        token= strtok(NULL," "); 
        modelo = token;

        strcat(strcpy(destinoStr, directorio), alumno); //destino == estudiantes/0572938
        strcat(destinoStr, "/"); //destino == estudiantes/0572938/
        strcat(destinoStr, modelo); //destino == estudiantes/0572938/A
        strcat(destinoStr, ".pdf"); //destino == estudiantes/0572938/A.pdf

        char* origenStr;
        
        if(strcmp(modelo,MODA)==0){
            origenStr = "examenes/A.pdf";
            
        }
        if(strcmp(modelo,MODB)==0)
        {
            origenStr = "examenes/B.pdf";

        }
        if(strcmp(modelo,MODC)==0){
            origenStr = "examenes/C.pdf";

        }
        
        link(origenStr,destinoStr);
       
    }

}

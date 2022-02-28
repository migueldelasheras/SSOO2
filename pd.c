#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    printf("Soy el proceso d");

/*
    kill(atoi(argv[0]),SIGINT);
    kill(atoi(argv[1]),SIGINT);
    kill(atoi(argv[2]),SIGINT);
    kill(getppid(),SIGINT);

*/
    kill(getppid(),SIGKILL);
    FILE *log = fopen("log.txt","a+");
    fputs("\nSe ha producido una interrupcion voluntaria ordenada por el usuario\n",log);

    char *const arg_list[] = {"/bin/bash","-c","rm -r estudiantes",NULL};
    execve("/bin/bash",arg_list,NULL);
    
    

}
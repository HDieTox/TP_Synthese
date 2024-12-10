#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>


#include "../headers/constants.h"

#include <unistd.h>
#include "../headers/constants.h"

enum redirection { SRC,DEST,ABS};

void displayWelcomeMsg(){
    write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE)) ;
}

void slicer(char* sliced[],char* string, char separator){
    
    char* strToken = strtok(string,&separator);
    int i = 0;

    while (strToken != NULL)
    {
        sliced[i] = strToken;
        strToken = strtok(NULL,&separator);
        i++;
    }
}

void betterPrompt(int signORexit,int duree,int signal){
    char betterPrompt[50] = {0};

    if (signORexit) {
        sprintf(betterPrompt,"enseash [exit:%d|%dms] %%",signORexit,duree);
    } else if (signORexit) {
        sprintf(betterPrompt,"enseash [signal:%d|%dms] %%",signal,duree);
    }
    write(STDOUT_FILENO,betterPrompt,strlen(betterPrompt));

}

void rep(){
    char buffer [BUFFER_SIZE*2] ={0};
    char* buffer_splited[2] ={0};

// =============== DEBUT REDIRECTION ===============

    enum redirection mode = SRC;

    slicer(buffer_splited,buffer,'<');
    if (buffer_splited[1] == NULL){
        slicer(buffer_splited,buffer,'>');
        mode = DEST;
    }
    if (buffer_splited[1] == NULL){
        mode = ABS;
    }

    int input, output;
    
    switch (mode){
    case ABS:
        input = STDIN_FILENO;
        output = STDOUT_FILENO;
        break;

    case SRC:
        input = open(buffer_splited[1],O_RDWR);
        output = STDOUT_FILENO;
        break;

    case DEST:
        input = STDIN_FILENO;
        output = open(buffer_splited[1],O_RDWR);
        break;

    default:
        break;
    }

// ================================================= 

    read(input,buffer,BUFFER_SIZE);

    buffer[strlen(buffer)-1] = '\0';

    char* commande[MAX_ARGS] = {0};
    slicer(commande,buffer,' ');
    
    if(strcmp("exit",commande[0]) == 0){
        write(output,GOODBYE,strlen(GOODBYE));
        exit(EXIT_SUCCESS);
    }

    pid_t ret;
    int status;
    ret = fork();

    struct timespec start, end;
    int duree = 0;

    clock_gettime(CLOCK_MONOTONIC,&start);
    if (ret == 0){
        execvp(commande[0],commande);
        exit(EXIT_FAILURE);
    }else{
        wait(&status);
    }
    clock_gettime(CLOCK_MONOTONIC,&end);
    duree = (end.tv_sec-start.tv_sec)*1000.0 + (end.tv_nsec-start.tv_nsec)/MILLION;
    
    betterPrompt(WIFEXITED(status),duree,WTERMSIG(status));
}
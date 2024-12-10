#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "../bin/constants.h"

#include <unistd.h>
#include "../bin/constants.h"

void displayWelcomeMsg(){
    write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE)) ;
}


void rep(){
    char buffer [BUFFER_SIZE] ={0};
    const char* separator = " ";
    char* commande[MAX_ARGS] = {0};
    
    write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
    read(STDIN_FILENO,buffer,BUFFER_SIZE);

    buffer[strlen(buffer)-1] = '\0';

    char* strToken = strtok(buffer,separator);
    int i = 0;

    while (strToken != NULL)
    {
        commande[i] = strToken;
        strToken = strtok(NULL,separator);
        i++;
    }
    
    if (strlen(buffer) <= 0){
        perror("Buffer length = 0\n");
        exit(EXIT_FAILURE);
    }
    
    if(strcmp("exit",commande[0]) == 0){
        exit(EXIT_SUCCESS);
    }

    pid_t ret = fork();

    if (ret == 0){
        execvp(commande[0],commande);
        exit(EXIT_FAILURE);
    }
    

}
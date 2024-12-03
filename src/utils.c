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
    
    write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
    read(STDIN_FILENO,buffer,BUFFER_SIZE);

    buffer[strlen(buffer)-1] = '\0';    

    if (strlen(buffer) <= 0){
        perror("Buffer length = 0\n");
        exit(EXIT_FAILURE);
    }
    
    pid_t ret = fork();

    if(ret == 0){
        execvp(buffer,NULL);
    }
    

}
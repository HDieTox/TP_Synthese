#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "../bin/constants.h"


void displayWelcomeMsg(){ // affiche un message d'accueil au lancement
    
    write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE)) ;
    
}
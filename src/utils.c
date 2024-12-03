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
    write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE)) ;
}

void rep(){
    char buffer[BUFFER_SIZE];

}
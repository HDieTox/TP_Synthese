#include <stdlib.h>
#include <stdio.h>

#include "bin/utils.h"

int main(int argc, char const *argv[])
{
    displayWelcomeMsg();
    while (1)
    {
        rep();
    }
    
    return EXIT_SUCCESS;
}

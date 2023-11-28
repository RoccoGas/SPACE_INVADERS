// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "allegro.h"

int main(){
    if (!initialize_allegro()) {
        printf("Unable to start because allegro was not properly initialized...");
        return -1;
    }

    destroy_allegro();
    return 0;
}



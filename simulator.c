//
// Created by wilke on 8/16/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#include <errno.h>
#include <time.h>
#include "memsim.h"


int main(const int argc, const char** argv){
    int
        wordsVirtual,
        wordsPhysical,
        frameWords,
        pageTableLocation,
        addr,
        value;
    char command = ' ';
    const char* FERROR = "File could not be read. Try again";
    const char* HELP = "%15s t <virtual_address>\n%15s r <virtual_address>\n%15s w <virtual_address>\n";
    const char* WELCOME = "Welcome to the Paged Memory Simulator\n";
    // end initial declarations //

    FILE *stream;
    stream = fopen(argv[1], "r");

    // get first four values from file
    fscanf(stream, "%d\n%d\n%d\n%d", &wordsVirtual, &wordsPhysical, &frameWords, &pageTableLocation);

    // Early return and error message if the first four values cannot be verified.
    if(!file_verification(wordsVirtual, wordsPhysical, frameWords, pageTableLocation)){
        printf("%s", FERROR);
        return -1;
    }

    // initialize consts for the number of bits used for the offset and the number of pages and frames needed to fit all
    // virtual memory words into physical memory
    const int offsetBits = (int) log2(frameWords); // number of bits used for offset
    const int numPages = wordsVirtual / frameWords; // number of pages

    // initialize an array with a capacity equal to the size of the physical memory indicated in the file
    int* physical_memory = malloc( sizeof(int[wordsPhysical]));

    // populate the array
    for (int i = 0, k; i < frameWords + numPages; ++i) {
        fscanf(stream, "%d", &k);
        physical_memory[i] = k;
    }

    // print welcome message
    printf("%s", WELCOME);

    // begin CLI
    while (true){ // Checking in loop for q to avoid executing a full loop on sentinel input.
        printf(">");
        scanf(" %c", &command); // consume whitespace and first argument

        if(command == 'h') {
            printf( HELP, "Address translation:", "Read from memory:", "Write to memory:");
            continue;
        }else if(command == 'q'){
            break;
        }

        // parse second command
        scanf("%d", &addr); // consume second operand when it is likely there is a second argument
        unsigned int p_addr = get_physical_address(addr, offsetBits, pageTableLocation, physical_memory);
        if (command == 't') {
            printf("%d -> %d\n", addr, p_addr);
        }else if (command == 'r') {
            printf("%d: %d\n", addr, read_value(p_addr, offsetBits, pageTableLocation, physical_memory));
        }else if (command == 'w') {
            // no longer checking if an address is in the page table, since all virtual addresses map to frames
            // outside the page table. (a virtual address can never address a page table entry)
            scanf("%d", &value); // get third arg, since we know there should be a third arg
            printf("%d: %d\n", addr, value);
            write_value(value, p_addr, offsetBits, pageTableLocation, physical_memory);
        }
    }
    // free heap allocated memory
    free(physical_memory);
    fclose(stream);
    return 0;
}


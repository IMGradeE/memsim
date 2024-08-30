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

/*
 * This function varies from the last by assuming that the frame numbers are to be stored as written in the file, and
 * that the frame numbers begin at an offset indicated on line 4, and all values in the set of lines
 * (4, offset)U[offset+page_count, EOF|virtual_words+page_count] are words to be stored within frames in physical memory.
 * */
void init_memory(FILE *stream, int *page_table_location, int *physical_memory, int page_count, int num_words_virtual,
                           int num_page_frame_words, int* mmu) {
    // page_table_location is always at line 4 in the file, list of mappings starts there and ends at 4+page_table_location
    fpos_t
        content_start,
        pt_beginning,
        content_gap_end;

    fgetpos(stream, &content_start);

    // move filepointer -> line before physical page table location
    for (int i = 0; i < *page_table_location; ++i) {
        fscanf(stream, "%*d");
    }

    // (Store a pointer to the location in the file where the frame numbers are stored)
    fgetpos(stream, &pt_beginning);

    int temp;
    // retrieve page_count entries and insert into page table starting at pt_beginning, loop until all page table entries
    // contain a frame number from the file

    int j = 0;
    while(j < page_count){
        fscanf(stream,"%d", &temp);
        mmu[j] = temp;
        ++j;
    }
    fgetpos(stream, &content_gap_end);
    fsetpos(stream, &content_start);

    for (int i = 0, l = 0, k, frameNumberWOffset; i < num_words_virtual + page_count; ++i, ++l) {
        if(i == *page_table_location){
            i += page_count;
            fsetpos(stream, &content_gap_end);

        }
        k = (l/num_page_frame_words); // this is (base + page)
        frameNumberWOffset = mmu[k] + (i%num_page_frame_words);
        int temp2;
        fscanf(stream, "%d\n", &temp2);
        physical_memory[frameNumberWOffset] = temp2;

    }
}



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
    int* mmu = malloc( sizeof(int[numPages]));

    // populate the array
    init_memory(stream, &pageTableLocation, physical_memory, numPages, wordsVirtual, frameWords, mmu);

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
        unsigned int p_addr = get_physical_address(addr, offsetBits, pageTableLocation, mmu);
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
    free(mmu);
    fclose(stream);
    return 0;
}


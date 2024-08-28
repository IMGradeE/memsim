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

int init_memory(FILE* stream, int* page_table_location, int* physical_memory, int page_count, int num_words_virtual, int num_page_frame_words){
    // page_table_location is always at line 4 in the file, list of mappings starts there and ends at 4+page_table_location
    const int FILEOFFSET = 4;

    // move fp -> beginning of page table entries
    for (int i = 0; i < *page_table_location; ++i) {
        fscanf(stream, "%*d");
    }
    // get the value for the physical page table location
    fscanf(stream, "%d", page_table_location);
    // store fpos
    fpos_t content_start;
    fgetpos(stream, &content_start);
    // reset fp to BOF
    fseek(stream,0,SEEK_SET);
    // initialize constants representing page table boundaries.
    const int
        pt_frame_interval = page_count >> 2,
        pt_lower_b = *page_table_location >> 2,
        pt_upper_b = pt_lower_b + pt_frame_interval,
        loop_bound = FILEOFFSET + page_count + pt_frame_interval;
    int temp;
    // retrieve page_count entries and insert into page table
    for (int i = 0, j = *page_table_location; i < loop_bound; ++i) {
        // skip first four entries and the frames we are writing to.
        if(i < FILEOFFSET) {
            fscanf(stream, "%*d");
        }else{
            fscanf(stream,"%d", &temp);
            if (temp < pt_lower_b || temp >= pt_upper_b){
                // insert frame numbers into physical memory starting from [page_table_location] up to [page_count - 1] for
                // (page_count) total page mappings, skipping frames that are values in the page table (4,5 in mem_file1).
                physical_memory[j] = temp;
                ++j;
            }
        }
    }
    // reset fp to the entry with the first piece of data
    fsetpos(stream, &content_start);

    // insert remaining entries into array
    for (int i = 0 ; i < num_words_virtual + page_count; ++i) {
        if(i == *page_table_location){
            i+= page_count;
        }
        fscanf(stream, "%d", &physical_memory[i]);
    }
    return pt_frame_interval << 2;
}


int main(const int argc, const char** argv){
    int
        num_words_virtual =0,
        num_words_physical=0,
        num_page_frame_words=0,
        page_table_location=0,
        temp=0;

    FILE *stream;
    if(argc > 1){
         stream = fopen(argv[1], "r");
    }
    else{
        return -1;
    }

    fscanf(stream, "%d\n%d\n%d\n%d", &num_words_virtual, &num_words_physical, &num_page_frame_words, &page_table_location);
    // Early return and error message if file parameters are not all powers of two.
    int t;
    t = file_verification(num_words_virtual, num_words_physical, num_page_frame_words, page_table_location);
    if(t == 0){
        printf("File could not be read or is of the wrong type. Please try again with a different file reference.");
        return -1;
    }

    const int addrSizeBitsPhysical = log2(num_words_physical);
    const int addrSizeBitsLogical  = log2(num_words_virtual);
    const int offsetNumBits = (int) log2(num_page_frame_words);
    const int frame_numBits = addrSizeBitsPhysical - offsetNumBits;
    const int page_numBits = addrSizeBitsLogical - offsetNumBits;

    const int numPages = num_words_virtual / num_page_frame_words; // number of pages
    const int numFrames = num_words_physical / num_page_frame_words;

    int* physical_memory = malloc( sizeof(int[num_words_physical]));
    // call init_memory
    int page_table_interval = init_memory(stream, &page_table_location, physical_memory, numPages, num_words_virtual, num_page_frame_words);
    char command;
    int addr;
    int value;

    while (true){
        printf("\nPress h for help, or Enter a command of the form <flag> <argument>: ");
        scanf(" %c", &command);

        if (command == 'q') {
            break;
        }else if(command == 'h') {
            printf(
                    "%15s t <virtual_address>\n"
                    "%15s r <virtual_address>\n"
                    "%15s w <virtual_address>\n", "Address translation:", "Read from memory:", "Write to memory:");
            continue;
        }
        scanf("%d", &addr);
        if (command == 't') {
            printf("Vaddr %d maps to the physical address %d\n",
                   addr,
                   get_physical_address(addr, offsetNumBits, page_table_location, physical_memory));
        }else if (command == 'r') {
            printf("Value stored at Vaddr %d = %d\n", addr,
                   read_value(addr, offsetNumBits, page_table_location, physical_memory));
        }else if (command == 'w') {
            scanf("%d", &value);
            printf("Setting value stored at Vaddr %d to %d\n", addr, value);
            int p_addr = get_physical_address(addr,offsetNumBits,page_table_location,physical_memory);
            if( p_addr >= page_table_location + page_table_interval ||p_addr < page_table_location ){
                write_value(value,addr, offsetNumBits, page_table_location, physical_memory);
                printf("Value stored at Vaddr %d = %d\n", addr, read_value(addr, offsetNumBits, page_table_location, physical_memory));
            }else{
                printf("Can't set value stored at Vaddr %d to %d because doing so would overwrite the page table.\n", addr, value);
            }
        }else{
            printf("Unrecognized command or format. Try h for help.\n");
        }

    }
    // free heap allocated memory
    free(physical_memory);
    fclose(stream);
    return 0;
}


// Submission:
// Submit your assignment as a zip file containing, the .c and .h files, the compiled .so library, the compiled executable, your additional memory files and a readme with every command you used to compile your library, and executable.  Including any commands used to set env variables, or generate intermediate steps (like the object files). //
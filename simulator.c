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
 * This function makes the following assumptions:
 *     the fourth line in the memory file indicates a range of lines in the memory file that contain frame numbers:
 *         the range in interval notation is (4, 4+{value at line 4}]
 *     the value at 4+{value at line 4}+1 is the location of the page table in physical memory.
 *     values in the range (4, 4+{value at line 4}] are inserted into physical memory starting at the location of the page table
 *         in physical memory at the position determined by the value in the memory file at line number 4+{value at line 4}+1,
 *         skipping any lines in the file whose values fall within the range :
 *             [physical_page_table_location, physical_page_table_location+page_count]
 *         until there are [page_count] frame numbers in the page table.
 *     values are then added to frames in physical memory from the lines in the file contained in the range:
 *         (4+{value at line 4}+1, {EOF||num_virtual_words}]
 *     these values are added into the frames defined in the page table, moving to the next frame when the number of words added to a frame
 *     modulus words_per_frame == 0
 *     when the operation is over the function returns.
 * */
void init_memory(FILE *stream, int *page_table_location, int *physical_memory, int page_count, int num_words_virtual,
                 int num_page_frame_words) {
    // page_table_location is always at line 4 in the file, list of mappings starts there and ends at 4+page_table_location
    fpos_t content_start;
    fpos_t pt_beginning;
    fpos_t bounds_check;
    fgetpos(stream, &pt_beginning); // (Store a pointer to the 4th location in the file)

    // move filepointer -> line before physical page table location
    for (int i = 0; i < *page_table_location; ++i) {
        fscanf(stream, "%*d");
    }

    // get the value for the physical page table location (the value at line 4+page_table_location)
    fscanf(stream, "%d", page_table_location);

    // store fpos where the memory contents begin
    fgetpos(stream, &content_start);

    // reset fp to pt_beginning
    fsetpos(stream, &pt_beginning);

    // initialize constants representing page table boundaries.
    const int pt_upper_b = *page_table_location+page_count; // indicates the first frame the page table does not own

    int temp;

    // retrieve page_count entries and insert into page table starting at pt_beginning, loop until all page table entries
    // contain a frame number from the file
    int j = *page_table_location;
    while((j < pt_upper_b) && (&bounds_check != &content_start)){
        fscanf(stream,"%d", &temp);
        temp *= num_page_frame_words;
        if (temp < *page_table_location || temp >= pt_upper_b){ // skip frame numbers that would map a vaddr to the page table
            // insert frame numbers into physical memory starting from [page_table_location] up to [page_count - 1] for
            // (page_count) total page mappings, skipping frames that are values in the page table (4,5 in mem_file1).
            physical_memory[j] = temp;
            ++j;
        }
        fgetpos(stream, &bounds_check); // ensures temp is never a memory word's value
    }

    // reset fp to the entry before the first piece of data
    fsetpos(stream, &content_start);

    // insert remaining entries into array
    for (int i = 0, l = 0, k, frameNumberWOffset; i < num_words_virtual + page_count; ++i, ++l) {

        if(i == *page_table_location){
            i+= page_count;
        }

        k = *page_table_location + (l/num_page_frame_words); // this is (base + page)
        frameNumberWOffset = physical_memory[k] + (i%num_page_frame_words);
        fscanf(stream, "%d", &physical_memory[frameNumberWOffset]);
    }

}

void init_memory_alternate(FILE *stream, int *page_table_location, int *physical_memory, int page_count, int num_words_virtual,
                    int num_page_frame_words) {
    // page_table_location is always at line 4 in the file, list of mappings starts there and ends at 4+page_table_location
    fpos_t content_start;
    fpos_t pt_beginning;
    fpos_t bounds_check;
    fgetpos(stream, &pt_beginning); // (Store a pointer to the 4th location in the file)

    // move filepointer -> line before physical page table location
    for (int i = 0; i < *page_table_location; ++i) {
        fscanf(stream, "%*d");
    }

    // store fpos where the memory contents begin
    fgetpos(stream, &content_start);

    // reset fp to pt_beginning
    fsetpos(stream, &pt_beginning);

    // initialize constants representing page table boundaries.
    const int pt_upper_b = *page_table_location + page_count; // indicates the first frame the page table does not own

    int temp;

    // retrieve page_count entries and insert into page table starting at pt_beginning, loop until all page table entries
    // contain a frame number from the file
    int j = *page_table_location;
    while((j < pt_upper_b) && (&bounds_check != &content_start)){
        fscanf(stream,"%d", &temp);
        temp *= num_page_frame_words;
        if (temp < *page_table_location || temp >= pt_upper_b){ // skip frame numbers that would map a vaddr to the page table
            // insert frame numbers into physical memory starting from [page_table_location] up to [page_count - 1] for
            // (page_count) total page mappings, skipping frames that are values in the page table (4,5 in mem_file1).
            physical_memory[j] = temp;
            ++j;
        }
        fgetpos(stream, &bounds_check); // ensures temp is never a memory word's value
    }

    // reset fp to the entry before the first piece of data
    fsetpos(stream, &content_start);

    // insert remaining entries into array
    for (int i = 0, l = 0, k, frameNumberWOffset; i < num_words_virtual + page_count; ++i, ++l) {

        if(i == *page_table_location){
            i+= page_count;
        }

        k = *page_table_location + (l/num_page_frame_words); // this is (base + page)
        frameNumberWOffset = physical_memory[k] + (i%num_page_frame_words);
        fscanf(stream, "%d", &physical_memory[frameNumberWOffset]);
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
    // populate the array
    init_memory_alternate(stream, &pageTableLocation, physical_memory, numPages, wordsVirtual, frameWords);

    // print welcome message
    printf("%s", WELCOME);

    // begin CLI
    while (true){ // Checking in loop for q to avoid executing a full loop on sentinel input.
        printf("> ");
        scanf(" %c", &command); // consume whitespace and first argument

        if(command == 'h') {
            printf( HELP, "Address translation:", "Read from memory:", "Write to memory:");
            continue;
        }else if(command == 'q'){
            break;
        }

        // parse second command
        scanf("%d", &addr); // consume second operand when it is likely there is a second argument
        if (command == 't') {
            printf("%d -> %d\n",
                   addr,
                   get_physical_address(addr, offsetBits, pageTableLocation, physical_memory)
                   );
        }else if (command == 'r') {
            printf("%d: %d\n",
                   addr,
                   read_value(addr, offsetBits, pageTableLocation, physical_memory)
                   );
        }else if (command == 'w') {
            // no longer checking if an address is in the page table, since all virtual addresses map to frames
            // outside the page table. (a virtual address can never address a page table entry)
            scanf("%d", &value); // get third arg, since we know there should be a third arg
            printf("%d: %d\n", addr, value);
            write_value(value, addr, offsetBits, pageTableLocation, physical_memory);
        }
    }
    // free heap allocated memory
    free(physical_memory);
    fclose(stream);
    return 0;
}


// Submission:
// Submit your assignment as a zip file containing, the .c and .h files, the compiled .so library, the compiled executable, your additional memory files and a readme with every command you used to compile your library, and executable.  Including any commands used to set env variables, or generate intermediate steps (like the object files). //
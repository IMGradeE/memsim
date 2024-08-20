//
// Created by wilke on 8/16/2024.
//
// Main params
// # mem_file - the name of the memory file to read in
//
// Verify the following are powers of two
// # Number of words in Virtual Memory
// # Number of words in Physical Memory
// # Number of words per page or frame
//
// Other Elements of Memory File
// # Page Table Location (Divisible by Page/Frame size)
// # Memory Contents (1 word per line)
//
// Derived variables:
// # address size 2^n (n is number of bits necessary to form addresses for the entire space)
// # number of bits for page number (high order n-k)
// # number of bits for the frame number (2^{m-k})
// # number of bits for the offset (lower order k bits)
//
// Structs:
// # Array to represent main memory
//
// CLI format
// Read:       r <v_addr>
// write:      w <v_addr> <value>
// translate:  t <v_addr>
// a

/*Pseudocode:
 * while command is not 'q':
 *  if command is 't'
 *    print the translated (i.e. physical) address corresponding to the entered virtual address
 *  else if command is 'r'
 *     print the value at address
 *  else if command is 'q':
 *     quit
 *  else :
 *     print a help message*/

int main(int argc, char** mem_file){
    // TODO verification
    int aSize, pageNumBits, frameNumBits, offsetNumBits;
    // TODO derive values
    // TODO malloc(n<int>) to array
    //
}
// Submission:
// Submit your assignment as a zip file containing, the .c and .h files, the compiled .so library, the compiled executable, your additional memory files and a readme with every command you used to compile your library, and executable.  Including any commands used to set env variables, or generate intermediate steps (like the object files). //
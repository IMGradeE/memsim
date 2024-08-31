
#include "memsim.h"
#include <stdbool.h>

//Check if a value is a power of two. One way to perform this check is to do a binary & between the value and the value minus 1. When the value is a power of two this will produce a 0 for all other values it will be non-zero.
bool is_power_of_2(unsigned int value){
    if ((value & (value-1)) == 0){
        return true;
    }else{
        return false;
    }
};

//Takes a virtual address and converts it to a physical address. The virtual address, the number of bits used for the offset, the starting location of the page table(s), and a pointer to the physical memory are also passed as parameters.

unsigned int get_physical_address(unsigned int virtual_address,
                                  unsigned int offset_bits,
                                  unsigned int page_table_loc,
                                  const int* physical_memory){
    unsigned int
            page_number = (virtual_address >> offset_bits),
            frame_number = physical_memory[page_number+page_table_loc],
            offset = virtual_address &((1 << offset_bits)-1);
    return (frame_number + offset);
};

//Takes a virtual address and returns the value at the corresponding physical address. The virtual address, the number of bits used for the offset, the starting location of the page table(s), and a pointer to the physical memory are also passed as parameters.
int read_value(unsigned int virtual_address,
               unsigned int page_mask,
               unsigned int page_table_loc,
               int* physical_memory){
    return physical_memory[virtual_address]; // not actually the virtual address
};

//Takes a value and a virtual address and stores the value at the corresponding physical address. The virtual address, the number of bits used for the offset, the starting location of the page table(s), and a pointer to the physical memory are also passed as parameters.
void write_value( int value,
                 unsigned int virtual_address,
                 unsigned int page_mask,
                 unsigned int page_table_loc,
                 int* physical_memory){

    physical_memory[virtual_address] = value;
};

// verification helper function
bool file_verification(const unsigned int num_w_v,
                       const unsigned int num_w_p,
                       const unsigned int num_p_f,
                       const unsigned int num_p_t_l){
    // Wasn't sure if I was allowed to initialize an extra array or use the target array, so I just did this
    bool check = true;
    check &= is_power_of_2(num_w_v);
    check &= is_power_of_2(num_w_p);
    check &= is_power_of_2(num_p_f);
    check &= (num_p_t_l%num_p_f == 0); // I forgot to do this lol
    return check;
}

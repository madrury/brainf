#include <stdio.h>
#include <stdlib.h>

/* bf_data:
 *    A structure for storing the internal brainfuck state.  Consists of an
 * array of bytes (chars) to hold data, and a data pointer that at all times
 * points to a byte in the data array.
 * Note: the last byte of the array is allways the null byte, this allows us
 * to make sure we never exceed the bounds of the data array.
 */

#ifndef BF_DATA
#define BF_DATA
// Length of internal array of data registers
#define DATA_LENGTH 1000
#define DATA_BOUNDARY_CHAR -128

typedef struct {
    char data_array[DATA_LENGTH];
    char* data_pointer;
} bf_data;
#endif

bf_data* setup_state();
void teardown_state(bf_data* bfd);
void increment_data_pointer(bf_data* bfd);
void decrement_data_pointer(bf_data* bfd);
void increment_byte(bf_data* bfd);
void decrement_byte(bf_data* bfd);
char get_byte(bf_data* bfd);
void output_byte(bf_data* bfd);
void set_byte(bf_data* bfd, char c);
void raise_data_error(void); 

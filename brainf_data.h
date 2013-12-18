#include <stdio.h>
#include <stdlib.h>

/* bf_data:
 *    A structure for storing the internal brainfuck state.  Consists of an
 * array of bytes (chars) to hold data, and a data pointer that at all times
 * points to a byte in the data array.
 *   Note: the first and last bytes in the data array are set to sentinal 
 * values, so that methods can perform out of bounds checks.  This sential 
 * value must be of char type, so it is always possible that this value 
 * could be a valid byte in the array.
 */

#ifndef BF_DATA
#define BF_DATA
// Length of internal array of data registers
#define DATA_LENGTH 1000
// Sentinal value to mark boundries of the data array
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

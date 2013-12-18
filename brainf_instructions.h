#include <stdio.h>
#include <stdlib.h>

/* bf_instructions:
 *    A structure for holding the instructions in a brainfuck program.  
 * Consists of an array of bytes represention the instructions in the
 * program, along with an instruction pointer that at all times points to 
 * the current instruction.
 */

#ifndef BF_INSTRUCTIONS
#define BF_INSTRUCTIONS
// Length of array used for storing the bf program
#define INSTRUCTION_LENGTH 5000

typedef struct {
    char instruction_array[INSTRUCTION_LENGTH];
    char* instruction_pointer;
} bf_instructions;
#endif

int is_valid(char inst);
bf_instructions* read_instructions(FILE* source);
void teardown_instructions(bf_instructions* bfi);
char get_instruction(bf_instructions* bfi);
void increment_instruction_pointer(bf_instructions* bfi);
void decrement_instruction_pointer(bf_instructions* bfi);
void move_forward_after_bracket(bf_instructions* bfi);
void move_backward_after_bracket(bf_instructions* bfi);

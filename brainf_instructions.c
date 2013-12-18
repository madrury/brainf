#include "brainf_instructions.h"

// Valid brainfuck instructions
#define NUM_VALID_INSTRUCTIONS 8
char valid_instructions[] = {'<', '>', '+', '-', '[', ']', ',', '.'};

int is_valid_instruction(char inst) {
    // Check if a byte represents a valid brainfuck instruction
    for(int i = 0; i < NUM_VALID_INSTRUCTIONS; i++) {
        if(inst == valid_instructions[i]) {return 1;}
    }
    return 0;
}

bf_instructions* read_instructions(FILE* source) {
/* read_instructions:
*     Read a file and use it to create a new brainfuck program.  
* Initialize the state of this object to ready the program for execution.
*/    
    // Create a new instruction object and set the instruction pointer to
    // the first instruction.
    bf_instructions* new_instructions = calloc(1, sizeof(bf_instructions));
    new_instructions->instruction_pointer = new_instructions->instruction_array;
    // Process the instruction file and fill the instruction object
    char ch;
    while((ch = getc(source)) != EOF) {
        if(is_valid_instruction(ch)) {
            *(new_instructions->instruction_pointer) = ch;
            (new_instructions->instruction_pointer)++;
        }
    }
    // Set the last byte to zero, this marks the end of the program
    *(new_instructions->instruction_pointer) = '\0';
    // Reset instruction pointer to beginning of program
    new_instructions->instruction_pointer = new_instructions->instruction_array;
    return new_instructions;
}

void teardown_instructions(bf_instructions* bfi) {
    free(bfi);
}

char get_instruction(bf_instructions* bfi) {
    return *(bfi->instruction_pointer);
}

void increment_instruction_pointer(bf_instructions* bfi) {
    (bfi->instruction_pointer)++;
}

void decrement_instruction_pointer(bf_instructions* bfi) {
    (bfi->instruction_pointer)--;
}

void move_forward_after_bracket(bf_instructions* bfi) {
/* move_forward_after_bracket:
 *    Called when an opening bracket [ is encountered upon loop termination.  
 * Search for the matching closing bracket ] and move the instruction pointer
 * to the subsequent instruction.
 */
    int bracket_counter = 0;
    char ch;
    while(1){
        increment_instruction_pointer(bfi);
        ch = get_instruction(bfi);
        if(ch == '[') {bracket_counter++;}
        if(ch == ']') {
            if(bracket_counter == 0) {break;}
            else {bracket_counter--;}
        }
    }
    increment_instruction_pointer(bfi);
}

void move_backward_after_bracket(bf_instructions* bfi) {
/* move_backwards_after_bracket:
 *    Called when a closing bracket ] is encountered during loop execution.
 * Search for the matching opening bracket [ and move the instruction pointer
 * to the subsequent instruction.
 */
    int bracket_counter = 0;
    char ch;
    while(1){
        decrement_instruction_pointer(bfi);
        ch = get_instruction(bfi);
        if(ch == ']') {bracket_counter++;}
        if(ch == '[') {
            if(bracket_counter == 0) {break;}
            else {bracket_counter--;}
        }
    }
    increment_instruction_pointer(bfi);
}

#include "brainf_instructions.h"

#define NUM_VALID_INSTRUCTIONS 8
char valid_instructions[] = {'<', '>', '+', '-', '[', ']', ',', '.'};

int is_valid_instruction(char inst) {
    for(int i = 0; i < NUM_VALID_INSTRUCTIONS; i++) {
        if(inst == valid_instructions[i]) {return 1;}
    }
    return 0;
}

bf_instructions* read_instructions(FILE* source) {
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
   // Reset instruction pointer to beginning of program
   *(new_instructions->instruction_pointer) = '\0';
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
    int bracket_counter = 0;
    // This function should only be called when the instruction pointer is
    // on an opening bracket.
    if(get_instruction(bfi) != '[') {raise_bracket_error();}
    // Look for the closing bracket and then move one past it
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
    int bracket_counter = 0;
    // This function should only be called when the instruction pointer is
    // on a closing bracket.
    if(get_instruction(bfi) != ']') {raise_bracket_error();}
    // Look for the opening bracket and then move one past it
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

void raise_bracket_error(void) {
    printf("Bracket error.");
    exit(EXIT_FAILURE);
}

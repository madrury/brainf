#include <stdio.h>
#include <stdlib.h>
#include "brainf_data.h"
#include "brainf_instructions.h"

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("You need to supply the path to a brainfuck program!\n");
        exit(EXIT_FAILURE);
    }

    // Open the user supplied program 
    FILE* brainf_program = fopen(argv[1], "r");
    if(brainf_program == NULL) {
        printf("Path to brainfuck program not valid!\n");
        exit(EXIT_FAILURE);
    }

    // Read program and setup empty state
    bf_instructions* instructions = read_instructions(brainf_program); 
    bf_data* state = setup_state(); 

    // Exectute program
    char inst, byte;
    while(1) {
        inst = get_instruction(instructions);
        switch(inst) {
            case '<': 
                decrement_data_pointer(state);
                increment_instruction_pointer(instructions);
                break;
            case '>': 
                increment_data_pointer(state);
                increment_instruction_pointer(instructions);
                break;
            case '+':
                increment_byte(state);
                increment_instruction_pointer(instructions);
                break;
            case '-':
                decrement_byte(state);
                increment_instruction_pointer(instructions);
                break;
            case '[':
                byte = get_byte(state);
                if(byte == '\0') {
                    move_forward_after_bracket(instructions); 
                }
                else {
                    increment_instruction_pointer(instructions);
                }
                break;
            case ']':
                byte = get_byte(state);
                if(byte != '\0') {
                    move_backward_after_bracket(instructions);
                }
                else {
                    increment_instruction_pointer(instructions);
                }
                break;
            case '.':
                output_byte(state);
                increment_instruction_pointer(instructions);
                break;
            case ',':
                byte = getchar();
                set_byte(state, byte);
                increment_instruction_pointer(instructions);
            case '\0':
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid instruction found!\n");
                exit(EXIT_FAILURE);
        }
    }
}

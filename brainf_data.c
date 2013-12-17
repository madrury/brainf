#include "brainf_data.h"

bf_data* setup_state() {
    // Allocate a new bf_data struct, and fill the boundries with null bytes.
    bf_data* new_data = calloc(1, sizeof(bf_data));
    new_data->data_array[0] = DATA_BOUNDARY_CHAR;
    new_data->data_array[DATA_LENGTH - 1] = DATA_BOUNDARY_CHAR;
    // Set the instruction pointer to the first non-null byte.
    new_data->data_pointer = new_data->data_array + 1;
    return new_data;
}

void teardown_state(bf_data* bfd) {
    // Free the memory for the bf_data struct
    free(bfd);
}

void increment_data_pointer(bf_data* bfd) {
    // Increment the data pointer, if out of bounds, kill process.
    (bfd->data_pointer)++;
    if(*(bfd->data_pointer) == DATA_BOUNDARY_CHAR) {
       raise_data_error();
    }
}

void decrement_data_pointer(bf_data* bfd) {
    // Decrement the data pointer, if out of bounds, kill process.
    (bfd->data_pointer)--;
    if(*(bfd->data_pointer) == DATA_BOUNDARY_CHAR) {
       raise_data_error();
    }
}

void increment_byte(bf_data* bfd) {
    (*(bfd->data_pointer))++;
}

void decrement_byte(bf_data* bfd) {
    (*(bfd->data_pointer))--;
}

char get_byte(bf_data* bfd) {
    return *(bfd->data_pointer);
}

void output_byte(bf_data* bfd) {
    putchar(*(bfd->data_pointer));
}

void set_byte(bf_data* bfd, char c) {
    *(bfd->data_pointer) = c;
}

void raise_data_error() {
    printf("Error: Data pointer out of bounds.");
    exit(EXIT_FAILURE);
}

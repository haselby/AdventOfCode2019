// Day2App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>


void compute(int* array_ptr, size_t array_length, int op_code_offset ) {
    //printf("element value at op code: %d\n", array_ptr[op_code_offset]);
    //printf("array_length: %d\n", array_length);
    //printf("op_code_offset: %d\n", op_code_offset);

    int a{};
    int b{};
    int c{};
    int index_a{};
    int index_b{};
    int index_c{};

    if (array_ptr[op_code_offset] == 1) {
        index_a= array_ptr[op_code_offset + 1];
        index_b = array_ptr[op_code_offset + 2];
        index_c = array_ptr[op_code_offset + 3];
        a = array_ptr[index_a];
        b = array_ptr[index_b];
        c = a + b;
        array_ptr[index_c] = c;
        printf("Op Code 1 Executed\n");
    }
    else if (array_ptr[op_code_offset] == 2) {
        index_a = array_ptr[op_code_offset + 1];
        index_b = array_ptr[op_code_offset + 2];
        index_c = array_ptr[op_code_offset + 3];
        a = array_ptr[index_a];
        b = array_ptr[index_b];
        c = a * b;
        array_ptr[index_c] = c;
        printf("Opt Code 2 Executed\n");

    }
    else if (array_ptr[op_code_offset] == 99) {

        printf("Opt Code 99 Executed\n");
        printf("Result: %d\n", array_ptr[0]);
        return;
    }
    else {
        printf("Danger Will Robinson. Abort. Abort\n");
        return;
    }

    compute(array_ptr, array_length, op_code_offset + 4);

}

int main()
{
    int op_code_init_pos = 0;
    //int input[] = {1,0,0,0,99};
    //int input[] = {2,3,0,3,99};
    //int input[] = {1,1,1,4,99,5,6,0,99};
    int input[] = { 1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 9, 1, 19, 1, 19, 5, 23, 1, 23, 5, 27, 2, 27, 10, 31, 1, 31, 9, 35, 1, 35, 5, 39, 1, 6, 39, 43, 2, 9, 43, 47, 1, 5, 47, 51, 2, 6, 51, 55, 1, 5, 55, 59, 2, 10, 59, 63, 1, 63, 6, 67, 2, 67, 6, 71, 2, 10, 71, 75, 1, 6, 75, 79, 2, 79, 9, 83, 1, 83, 5, 87, 1, 87, 9, 91, 1, 91, 9, 95, 1, 10, 95, 99, 1, 99, 13, 103, 2, 6, 103, 107, 1, 107, 5, 111, 1, 6, 111, 115, 1, 9, 115, 119, 1, 119, 9, 123, 2, 123, 10, 127, 1, 6, 127, 131, 2, 131, 13, 135, 1, 13, 135, 139, 1, 9, 139, 143, 1, 9, 143, 147, 1, 147, 13, 151, 1, 151, 9, 155, 1, 155, 13, 159, 1, 6, 159, 163, 1, 13, 163, 167, 1, 2, 167, 171, 1, 171, 13, 0, 99, 2, 0, 14, 0 };
    input[1] = 12;
    input[2] = 2;
    size_t input_length = sizeof(input) / sizeof(int);
    compute(input, input_length, op_code_init_pos);

}



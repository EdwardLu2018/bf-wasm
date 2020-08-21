#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>

#include "bf_mem.h"
#include "bf_stack.h"
#include "bf_jmp_dict.h"

// #define DEBUG

static bf_jmp_dict *create_jmp_dict(char *program, long length) {
    uint32_t pos, jmp;
    bf_stack *stack = NULL;
    bf_jmp_dict *dict = bf_jmp_dict_create(length / 10);
    char contains_loop = 0;

    for (uint32_t pc = 0; pc < length; ++pc) {
        if (program[pc] == '[') {
            if (!contains_loop) contains_loop = 1;
            bf_stack_push(&stack, pc);
        }
        if (program[pc] == ']') {
            pos = bf_stack_pop(&stack);
            jmp = pc;
            bf_jmp_dict_insert(dict, pos, jmp);
            bf_jmp_dict_insert(dict, jmp, pos);
        }
    }
    if (contains_loop) {
        assert(stack == NULL);
    }
    return dict;
}

int eval(char *program, long length) {
    bf_mem *memory = bf_mem_create();
    bf_jmp_dict *dict = create_jmp_dict(program, length);

    for (uint32_t pc = 0; pc < length; ++pc) {
        switch (program[pc]) {
            case '+':
                bf_mem_incr(memory);
                break;
            case '-':
                bf_mem_decr(memory);
                break;
            case '<':
                bf_mem_move_left(memory);
                break;
            case '>':
                bf_mem_move_right(memory);
                break;
            case ',':
                bf_mem_put(memory, getchar());
                break;
            case '.':
                putchar(bf_mem_get(memory));
                break;
            case '[':
                if (bf_mem_get(memory) == 0) {
                    pc = bf_jmp_dict_get(dict, pc);
                }
                break;
            case ']':
                if (bf_mem_get(memory) != 0) {
                    pc = bf_jmp_dict_get(dict, pc);
                }
                break;
            default:
                break;
        }
    }

#ifdef DEBUG
        bf_mem_print(memory);
        bf_jmp_dict_print(dict);
#endif

    bf_mem_free(memory);
    bf_jmp_dict_free(dict);

    return 0;
}

int main(int argc, char* argv[]) {
    int opt;
    long length;
    FILE *fileptr;
    char *filename = NULL, *program = 0;
    char *usg = "Usage: ./bf -f <file.bf>\n";

    // parse arguments
    while ((opt = getopt(argc, argv, "hf:")) > 0) {
        switch (opt) {
        case 'f':
            filename = optarg;
            break;
        case 'h':
        default:
            fprintf(stderr, "%s", usg);
            exit(1);
        }
    }

    fileptr = fopen(filename, "r");
    if (fileptr == NULL){
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // get text of file as string
    fseek(fileptr, 0, SEEK_END);
    length = ftell(fileptr);
    fseek(fileptr, 0, SEEK_SET);
    program = malloc(length);
    if (program == NULL) {
        printf("malloc failed\n");
        exit(0);
    }
    fread(program, 1, length, fileptr);

    // eval program
    eval(program, length);

    free(program);
    fclose(fileptr);

    return 0;
}

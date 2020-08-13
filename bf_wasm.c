#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>

#include <emscripten/emscripten.h>

#include "bf_mem.h"
#include "bf_stack.h"
#include "bf_jmp_dict.h"

// #define DEBUG

static bf_jmp_dict *create_jmp_dict(char *program, long length) {
    uint32_t pos, jmp;
    bf_stack *stack = NULL;
    bf_jmp_dict *dict = bf_jmp_dict_create(length / 10);
    bool contains_loop = false;

    for (uint32_t pc = 0; pc < length; ++pc) {
        if (program[pc] == '[') {
            if (!contains_loop) contains_loop = true;
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

EMSCRIPTEN_KEEPALIVE
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

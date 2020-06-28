#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    char *contents;
    uint16_t size;
    uint16_t curr_idx;
} bf_mem;

bf_mem *bf_mem_create();
char bf_mem_get(bf_mem *memory);
int bf_mem_incr(bf_mem *memory);
int bf_mem_decr(bf_mem *memory);
int bf_mem_move_right(bf_mem *memory);
int bf_mem_move_left(bf_mem *memory);
int bf_mem_put(bf_mem *memory, char c);
int bf_mem_free(bf_mem *memory);
void bf_mem_print(bf_mem *memory);

#endif // MEM_H

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
} bf_memory;

bf_memory *bf_memory_create();
char bf_memory_get(bf_memory *memory);
int bf_memory_incr(bf_memory *memory);
int bf_memory_decr(bf_memory *memory);
int bf_memory_append(bf_memory *memory);
int bf_memory_move_right(bf_memory *memory);
int bf_memory_put(bf_memory *memory, char c);
int bf_memory_move_left(bf_memory *memory);
int bf_memory_free(bf_memory *memory);
void bf_memory_print(bf_memory *memory);

#endif // MEM_H

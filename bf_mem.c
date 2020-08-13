#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bf_mem.h"

bf_mem *bf_mem_create() {
    bf_mem *memory = (bf_mem *)malloc(sizeof(bf_mem));
    if (memory == NULL) {
        printf("malloc failed\n");
        exit(0);
    }
    memory->curr_idx = 0;
    memory->size = 1;
    memory->contents = (uint8_t *)calloc(memory->size, sizeof(uint8_t));
    return memory;
}

uint8_t bf_mem_get(bf_mem *memory) {
    return memory->contents[memory->curr_idx];
}

int bf_mem_incr(bf_mem *memory) {
    memory->contents[memory->curr_idx]++;
    return 0;
}

int bf_mem_decr(bf_mem *memory) {
    memory->contents[memory->curr_idx]--;
    return 0;
}

static int bf_mem_append(bf_mem *memory) {
    uint8_t *new_contents;

    ++memory->size;
    new_contents = (uint8_t *)realloc(memory->contents, memory->size * sizeof(uint8_t));
    if (new_contents == NULL) {
        printf("realloc failed\n");
        exit(0);
    }
    new_contents[memory->size-1] = 0;
    memory->contents = new_contents;
    return 0;
}

int bf_mem_move_left(bf_mem *memory) {
    if (memory->curr_idx > 0) {
        --memory->curr_idx;
    }
    return 0;
}

int bf_mem_move_right(bf_mem *memory) {
    ++memory->curr_idx;
    if (memory->curr_idx >= memory->size) {
        bf_mem_append(memory);
    }
    return 0;
}

int bf_mem_put(bf_mem *memory, uint8_t c) {
    memory->contents[memory->curr_idx] = c;
    return 0;
}

int bf_mem_free(bf_mem *memory) {
    free(memory->contents);
    free(memory);
    return 0;
}

void bf_mem_print(bf_mem *memory) {
    printf("\n-- Memory --\n");
    for (size_t i = 0; i < memory->size; i++) {
        printf("[%d]", memory->contents[i]);
        if (i != 0 && i % 15 == 0)
            printf("\n");
    }
    printf("\n");
}

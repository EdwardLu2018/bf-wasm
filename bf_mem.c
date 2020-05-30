#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bf_mem.h"

bf_memory *bf_memory_create() {
    bf_memory *memory = (bf_memory *)malloc(sizeof(bf_memory));
    if (memory == NULL) {
        printf("malloc failed\n");
        exit(0);
    }
    memory->curr_idx = 0;
    memory->size = 1;
    memory->contents = (char *)calloc(memory->size, sizeof(char));
    return memory;
}

char bf_memory_get(bf_memory *memory) {
    return memory->contents[memory->curr_idx];
}

int bf_memory_incr(bf_memory *memory) {
    memory->contents[memory->curr_idx]++;
    return 0;
}

int bf_memory_decr(bf_memory *memory) {
    memory->contents[memory->curr_idx]--;
    return 0;
}

int bf_memory_append(bf_memory *memory) {
    char *new_contents;

    ++memory->size;
    new_contents = (char *)realloc(memory->contents, memory->size * sizeof(char));
    if (new_contents == NULL) {
        printf("realloc failed\n");
        exit(0);
    }
    memory->contents = new_contents;
    return 0;
}

int bf_memory_move_right(bf_memory *memory) {
    ++memory->curr_idx;
    if (memory->curr_idx >= memory->size) {
        bf_memory_append(memory);
    }
    return 0;
}

int bf_memory_put(bf_memory *memory, char c) {
    memory->contents[memory->curr_idx] = c;
    return 0;
}

int bf_memory_move_left(bf_memory *memory) {
    if (memory->curr_idx > 0) {
        --memory->curr_idx;
    }
    return 0;
}

int bf_memory_free(bf_memory *memory) {
    free(memory->contents);
    free(memory);
    return 0;
}

void bf_memory_print(bf_memory *memory) {
    printf("\n-- Memory --\n");
    for (size_t i = 0; i < memory->size; i++) {
        printf("[%d]", memory->contents[i]);
        if (i != 0 && i % 10 == 0)
            printf("\n");
    }
    printf("\n");
}

#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct jmp_elem {
    uint32_t pos;
    uint32_t jmp;
    struct jmp_elem *next;
} bf_jmp_elem;

typedef struct {
    size_t size;
    size_t num_elems;
    bf_jmp_elem **elems;
} bf_jmp_dict;

bf_jmp_dict *bf_jmp_dict_create(size_t size);
bf_jmp_elem *bf_jmp_elem_create(uint32_t pos, uint32_t jmp);
int bf_jmp_dict_insert(bf_jmp_dict *dict, uint32_t pos, uint32_t jmp);
uint32_t bf_jmp_dict_get(bf_jmp_dict *dict, uint32_t pos);
int bf_jmp_dict_free(bf_jmp_dict *dict);
void bf_jmp_dict_print(bf_jmp_dict *dict);

#endif // DICT_H

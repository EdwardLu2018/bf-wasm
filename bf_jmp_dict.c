#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "bf_jmp_dict.h"

bf_jmp_dict *bf_jmp_dict_create(size_t size) {
    bf_jmp_dict *jmp_dict = (bf_jmp_dict *)malloc(sizeof(bf_jmp_dict));
    if (jmp_dict == NULL) {
        printf("malloc failed\n");
        exit(0);
    }
    jmp_dict->size = size;
    jmp_dict->num_elems = 0;
    jmp_dict->elems = (bf_jmp_elem **)calloc(size, sizeof(bf_jmp_elem *));
    if (jmp_dict->elems == NULL) {
        printf("calloc failed\n");
        exit(0);
    }
    return jmp_dict;
}

bf_jmp_elem *bf_jmp_elem_create(uint32_t pos, uint32_t jmp) {
    bf_jmp_elem *elem = (bf_jmp_elem *)malloc(sizeof(bf_jmp_elem));
    if (elem == NULL) {
        printf("malloc failed\n");
        exit(0);
    }
    elem->next = NULL;
    elem->pos = pos;
    elem->jmp = jmp;
    return elem;
}

int bf_jmp_dict_insert(bf_jmp_dict *dict, uint32_t pos, uint32_t jmp) {
    size_t idx = pos % dict->size;
    bf_jmp_elem *to_add = bf_jmp_elem_create(pos, jmp);
    to_add->next = dict->elems[idx];
    dict->elems[idx] = to_add;
    ++dict->num_elems;
    return 0;
}

uint32_t bf_jmp_dict_get(bf_jmp_dict *dict, uint32_t pos) {
    size_t idx = pos % dict->size;
    bf_jmp_elem *curr = dict->elems[idx];
    for (; curr != NULL; curr = curr->next) {
        if (curr->pos == pos) {
            return curr->jmp;
        }
    }
    return -1;
}

int bf_jmp_dict_free(bf_jmp_dict *dict) {
    bf_jmp_elem *ptr;
    for (size_t i = 0; i < dict->size; ++i) {
        if (dict->elems[i] != NULL) {
            while (dict->elems[i] != NULL) {
                ptr = dict->elems[i];
                dict->elems[i] = dict->elems[i]->next;
                free(ptr);
            }
        }
    }
    free(dict->elems);
    free(dict);
    return 0;
}

void bf_jmp_dict_print(bf_jmp_dict *dict) {
    printf("\n-- Jump Table --\n");
    bf_jmp_elem *ptr;
    size_t cnt = 0;
    for (size_t i = 0; i < dict->size; ++i) {
        if ((ptr = dict->elems[i]) != NULL) {
            for (; ptr != NULL; ptr = ptr->next) {
                if (++cnt % 10 == 0) {
                    printf("(%u, %u)\n", ptr->pos, ptr->jmp);
                }
                else {
                    printf("(%u, %u) ", ptr->pos, ptr->jmp);
                }
            }
        }
    }
    printf("\n");
}

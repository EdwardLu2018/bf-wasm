#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct stack {
    uint32_t pc;
    struct stack *next;
} bf_stack;

bf_stack *bf_stack_create(uint32_t pc);
int bf_stack_push(bf_stack **stack, uint32_t pc);
uint32_t bf_stack_pop(bf_stack **stack);
int bf_stack_free(bf_stack *stack);

#endif // STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "bf_stack.h"

bf_stack *bf_stack_create(uint32_t pc) {
    bf_stack *stack = (bf_stack *)malloc(sizeof(bf_stack));
    if (stack == NULL) {
        printf("malloc failed\n");
        exit(0);
    }
    stack->next = NULL;
    stack->pc = pc;
    return stack;
}

int bf_stack_push(bf_stack **stack, uint32_t pc) {
    bf_stack *to_add = bf_stack_create(pc);
    to_add->next = *stack;
    *stack = to_add;
    return 0;
}

uint32_t bf_stack_pop(bf_stack **stack) {
    assert(stack != NULL);
    bf_stack *popped = *stack;
    uint32_t res = popped->pc;
    *stack = popped->next;
    popped->next = NULL;
    bf_stack_free(popped);
    return res;
}

int bf_stack_free(bf_stack *stack) {
    bf_stack *temp;
    while(stack != NULL) {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
    return 0;
}

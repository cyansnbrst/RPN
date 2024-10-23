#ifndef STACK_H
#define STACK_H

#include "lexemes.h"

typedef struct node {
    lexeme data;
    struct node *next;
} node;

typedef struct stack {
    int size;
    node *top;
} stack;

stack *init();
void push(stack *stack, lexeme value);
lexeme pop(stack *stack);
void destroy_stack(stack *stack);

#endif
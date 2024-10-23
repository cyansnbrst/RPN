#include "stack.h"

stack *init(void) {
    stack *new_stack = malloc(sizeof(stack));

    if (new_stack != NULL) {
        new_stack->size = 0;
        new_stack->top = NULL;
    }

    return new_stack;
}

void push(stack *root, lexeme value) {
    node *new_node = malloc(sizeof(node));

    if (new_node != NULL) {
        new_node->data = value;
        new_node->next = root->top;
        root->top = new_node;
        root->size++;
    }
}

lexeme pop(stack *root) {
    lexeme popped = root->top->data;

    if (root->top) {
        node *temp = root->top;
        root->top = root->top->next;
        root->size--;
        free(temp);
    }

    return popped;
}

void destroy_stack(stack *root) {
    node *current = NULL;

    while (root->top != NULL) {
        current = root->top;
        root->top = root->top->next;
        free(current);
    }

    free(root);
}
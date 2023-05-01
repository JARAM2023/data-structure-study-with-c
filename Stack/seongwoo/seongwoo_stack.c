#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

typedef struct {
    int size;
    node* top;
} stack;

stack* make_stack() {
    stack* s = (stack*)malloc(sizeof(stack));

    if (s == NULL)
        return NULL;
    
    s->size = 0;
    s->top = NULL;
    return s;
}

int push(stack* s, int data) {
    if (s == NULL)
        return -1;

    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    if (s->size == 0) {
        new_node->prev = NULL;
    } else {
        s->top->next = new_node;
        new_node->prev = s->top;
    }

    s->top = new_node;
    s->size++;
    return 0;
}

int pop(stack* s) {
    if (s == NULL || s->size == 0)
        return -1;

    int pop_data = s->top->data;

    if (s->size == 1) {
        free(s->top);
        s->top = NULL;
    } else {
        s->top = s->top->prev;
        s->top->next->prev = NULL;
        free(s->top->next);
        s->top->next = NULL;
    }
    s->size--;

    return pop_data;
}

int top(stack* s) {
    if (s == NULL || s->size == 0)
        return -1;

    return s->top->data;
}

int stack_size(stack* s) {
    return s->size;
}

int is_empty(stack* s) {
    return !(s->size);
}

int delete_stack(stack* s) {
    if (s == NULL)
        return -1;
    
    while (s->size != 0) {
        pop(s);
    }
    
    free(s);
    s = NULL;
    return 0;
}

int main() {
    stack* s = make_stack();

    for (int i = 0; i < 10; i++)
        push(s, i);
    
    printf("top: %d\n", top(s));

    for (int i = 0; i < 10; i++)
        printf("pop: %d\n", pop(s));

    printf("pop: %d\n", pop(s));

    delete_stack(s);
    return 0;
}
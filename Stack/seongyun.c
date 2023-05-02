#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int value;
    struct _Node* prev;
} Node;

typedef struct _Stack{
    Node* top;
    int size;
} Stack;


Node* create_node(int value){
    Node* node = (Node*)malloc(sizeof(Node));

    node -> prev = NULL;
    node -> value = value;

    return node;
}


Stack* create_stack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    Node* top = create_node(0);

    stack->top = top;
    stack->size = 0;

    return stack;
}

void push(Stack* stack, int value){
    Node* new_node = create_node(value);
    new_node->prev = stack->top;
    stack->top = new_node;
    stack->size++;
}

int pop(Stack* stack){
    stack->size--;
    int value = stack->top->value;
    Node* prev_node = stack->top->prev;
    free(stack->top);

    stack->top = prev_node;
    return value;
}

int top(Stack* stack){
    return stack->top->value;
}


int main(void){
    Stack* stack = create_stack();
    push(stack, 1);
    printf("#1: %d\n", top(stack));

    push(stack, 2);
    printf("#2: %d\n", top(stack));

    printf("#1: %d\n", pop(stack));
    printf("#2: %d\n", pop(stack));
    return 0;
}
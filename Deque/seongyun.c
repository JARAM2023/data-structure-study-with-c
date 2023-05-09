#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int value;
    struct _Node* next;
    struct _Node* prev;
} Node;


typedef struct _Deque{
    Node* front;
    Node* rear;
    int size;
} Deque;


Node* create_node(int value){
    Node* node = (Node*)malloc(sizeof(Node));

    node -> next = NULL;
    node -> value = value;

    return node;
}


Deque* create_queue(){
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    Node* node = create_node(0);

    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;

    return deque;
}


void enqueue_back(Deque* deque, int value){
    Node* new_node = create_node(value);

    if (deque->size == 0) {
        deque->front= new_node;
        deque->rear = new_node;
    }
    else {
        new_node->prev = deque->rear;
        deque->rear->next = new_node;
        deque->rear = new_node;
    }

    deque->size++;
}


void enqueue_front(Deque* deque, int value){
    Node* new_node = create_node(value);

    if (deque->size == 0) {
        deque->front= new_node;
        deque->rear = new_node;
    }
    else {
        new_node->next = deque->front;
        deque->front->prev = new_node;
        deque->front = new_node;
    }

    deque->size++;
}


int dequeue_front(Deque* deque){
    if(deque->size <= 0) return 0;

    int value = deque->front->value;

    Node* next_node = deque->front->next;

    free(deque->front);
    deque->size--;

    deque->front = next_node;

    return value;
}

int dequeue_back(Deque* deque){
    if(deque->size <= 0) return 0;

    int value = deque->rear->value;

    Node* prev_node = deque->rear->prev;

    free(deque->rear);
    deque->size--;

    deque->rear = prev_node;

    return value;
}


int front(Deque* deque){
    return deque->front->value;
}

int back(Deque* deque){
    return deque->rear->value;
}


int main(void){
    Deque* deque = create_queue();
    enqueue_front(deque, 1);
    printf("#1: %d\n", front(deque));
    printf("#1: %d\n", back(deque));
    enqueue_back(deque, 2);
    printf("#2: %d\n", front(deque));
    printf("#2: %d\n", back(deque));

    printf("#3: %d\n", dequeue_front(deque));
    printf("#3: %d\n", dequeue_back(deque));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int value;
    struct _Node* next;
} Node;


typedef struct _Queue{
    Node* front;
    Node* rear;
    int size;
} Queue;


Node* create_node(int value){
    Node* node = (Node*)malloc(sizeof(Node));

    node -> next = NULL;
    node -> value = value;

    return node;
}


Queue* create_queue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    Node* node = create_node(0);

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;

    return queue;
}


void enqueue(Queue* queue, int value){
    Node* new_node = create_node(value);

    if (queue->size == 0){
        queue->front= new_node;
        queue->rear = new_node;
    }

    queue->rear->next = new_node;
    queue->rear = new_node;

    queue->size++;
}


int dequeue(Queue* queue){
    if(queue->size <= 0) return 0;

    queue->size--;
    int value = queue->front->value;

    Node* next_node = queue->front->next;

    free(queue->front);

    queue->front = next_node;

    return value;
}


int front(Queue* queue){
    return queue->front->value;
}


int main(void){
    Queue* queue = create_queue();
    enqueue(queue, 1);
    printf("#1: %d\n", front(queue));
    enqueue(queue, 2);
    printf("#2: %d\n", front(queue));

    printf("#1: %d\n", dequeue(queue));
    printf("#2: %d\n", dequeue(queue));
    return 0;
}

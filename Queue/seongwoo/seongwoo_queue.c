#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

typedef struct {
    int size;
    node* in;
    node* out;
} queue;

queue* make_queue() {
    queue* q = (queue*)malloc(sizeof(queue));

    if (q == NULL)
        return NULL;
    
    q->size = 0;
    q->in = NULL;
    q->out = NULL;
    return q;
}

int enqueue(queue* q, int data) {
    if (q == NULL)
        return -1;

    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    if (q->size == 0) {
        new_node->prev = NULL;
        q->out = new_node;
    } else {
        q->in->next = new_node;
        new_node->prev = q->in;
    }

    q->in = new_node;
    q->size++;
    return 0;
}

int dequeue(queue* q) {
    if (q == NULL || q->size == 0)
        return -1;

    int dequeue_data = q->out->data;

    if (q->size == 1) {
        free(q->out);
        q->out = NULL;
        q->in = NULL;
    } else {
        q->out = q->out->next;
        q->out->prev->next = NULL;
        free(q->out->prev);
        q->out->prev = NULL;
    }
    q->size--;

    return dequeue_data;
}

int peek(queue* q) {
    if (q == NULL || q->size == 0)
        return -1;

    return q->out->data;
}

int queue_size(queue* q) {
    return q->size;
}

int is_empty(queue* q) {
    return !(q->size);
}

int delete_queue(queue* q) {
    if (q == NULL)
        return -1;
    
    while (q->size != 0) {
        dequeue(q);
    }
    
    free(q);
    q = NULL;
    return 0;
}

int main() {
    queue* q = make_queue();

    for (int i = 0; i < 10; i++)
        enqueue(q, i);
    
    printf("peek: %d\n", peek(q));
    
    for (int i = 0; i < 10; i++)
        printf("dequeue: %d\n", dequeue(q));

    printf("dequeue: %d\n", dequeue(q));

    delete_queue(q);
    return 0;
}
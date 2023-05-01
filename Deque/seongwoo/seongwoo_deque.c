#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

typedef struct {
    int size;
    node* back;
    node* front;
} deque;

deque* make_deque() {
    deque* d = (deque*)malloc(sizeof(deque));

    if (d == NULL)
        return NULL;
    
    d->size = 0;
    d->back = NULL;
    d->front = NULL;
    return d;
}

int push_front(deque* d, int data) {
    if (d == NULL)
        return -1;

    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    if (d->size == 0) {
        new_node->prev = NULL;
        d->back = new_node;
    } else {
        d->front->next = new_node;
        new_node->prev = d->front;
    }

    d->front = new_node;
    d->size++;
    return 0;
}

int push_back(deque* d, int data) {
    if (d == NULL)
        return -1;

    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->prev = NULL;

    if (d->size == 0) {
        new_node->next = NULL;
        d->front = new_node;
    } else {
        d->back->prev = new_node;
        new_node->next = d->back;
    }

    d->back = new_node;
    d->size++;
    return 0;
}

int pop_front(deque* d) {
    if (d == NULL || d->size == 0)
        return -1;

    int pop_data = d->front->data;

    if (d->size == 1) {
        free(d->front);
        d->front = NULL;
        d->back = NULL;
    } else {
        d->front = d->front->prev;
        d->front->next->prev = NULL;
        free(d->front->next);
        d->front->next = NULL;
    }
    d->size--;

    return pop_data;
}

int pop_back(deque* d) {
    if (d == NULL || d->size == 0)
        return -1;

    int pop_data = d->back->data;

    if (d->size == 1) {
        free(d->back);
        d->back = NULL;
        d->front = NULL;
    } else {
        d->back = d->back->next;
        d->back->prev->next = NULL;
        free(d->back->prev);
        d->back->prev = NULL;
    }
    d->size--;

    return pop_data;
}

int front(deque* d) {
    if (d == NULL || d->size == 0)
        return -1;

    return d->front->data;
}

int back(deque* d) {
    if (d == NULL || d->size == 0)
        return -1;

    return d->back->data;
}

int deque_size(deque* d) {
    return d->size;
}

int is_empty(deque* d) {
    return !(d->size);
}

int delete_deque(deque* d) {
    if (d == NULL)
        return -1;
    
    while (d->size != 0) {
        pop_front(d);
    }
    
    free(d);
    d = NULL;
    return 0;
}

int main() {
    deque* d = make_deque();

    for (int i = 0; i < 10; i++)
        push_front(d, i);
    
    printf("front: %d\n", front(d));
    
    for (int i = 0; i < 10; i++)
        push_back(d, i);
    
    printf("back: %d\n", back(d));
    
    for (int i = 0; i < 10; i++)
        printf("pop_front: %d\n", pop_front(d));
    
    for (int i = 0; i < 10; i++)
        printf("pop_back: %d\n", pop_back(d));

    printf("pop_front: %d\n", pop_front(d));
    printf("pop_back: %d\n", pop_back(d));

    delete_deque(d);
    return 0;
}
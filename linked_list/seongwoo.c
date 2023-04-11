#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

typedef struct {
    int size;
    node* first;
    node* last;
} linked_list;

linked_list* make_linked_list() {
    linked_list* list = (linked_list*)malloc(sizeof(linked_list));

    if (list == NULL)
        return NULL;

    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}

int insert_node_last(linked_list* list, int data) {
    if (list == NULL)
        return -1;

    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    if (list->size == 0) {
        list->first = new_node;
        new_node->prev = NULL;
    } else {
        list->last->next = new_node;
        new_node->prev = list->last;
    }

    list->last = new_node;

    list->size++;
    return 0;
}

int print_list(linked_list* list) {
    if (list == NULL)
        return -1;

    node* current_node = list->first;
    while (current_node != NULL) {
        printf("%d -> ", current_node->data);
        current_node = current_node->next;
    }
    printf("NULL\n");
    return 0;
}

int remove_node_last(linked_list* list) {
    if (list == NULL)
        return -1;

    if (list->size == 1) {
        list->last->prev = NULL;
        free(list->last);
        list->first = NULL;
        list->last = NULL;
    } else {
        list->last = list->last->prev;
        list->last->next->prev = NULL;
        free(list->last->next);
        list->last->next = NULL;
    }
    list->size--;

    return 0;
}

int delete_linked_list(linked_list* list) {
    if (list == NULL)
        return -1;
    
    while (list->size != 0) {
        remove_node_last(list);
    }
    
    free(list);
    list = NULL;
    return 0;
}

int print_index(linked_list* list, int index) {
    if (list == NULL || list->size <= index)
        return -1;
    
    node* current_node = list->first;
    for (int i = 0; i < index; i++) {
        current_node = current_node->next;
    }
    printf("index %d: %d\n", index, current_node->data);

    return 0;
}

/*
int insert_node_index(linked_list* list, int data, int index) {
    if (list == NULL || list->size < index)
        return -1;
    
    node* new_prev_node = list->first;
    for (int i = 0; i < index; i++) {
        new_prev_node = new_prev_node->next;
    }
    node* new_next_node = new_prev_node->next;
    
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;

    if (new_prev_node != NULL)
        new_prev_node->next = new_node;
    new_node->prev = new_prev_node;

    if (new_next_node != NULL)
        new_next_node->prev = new_node;
    new_node->next = new_next_node;



    if (list->size == 0) {
        list->first = new_node;
        new_node->prev = NULL;
    } else {
        list->last->next = new_node;
        new_node->prev = list->last;
    }

    list->last = new_node;

    list->size++;


    return 0;
}
*/

int main() {
    linked_list* list = make_linked_list();

    print_list(list);

    for (int i = 0; i < 10; i++)
        insert_node_last(list, i);
    
    print_list(list);
    print_index(list, 5);

    for (int i = 0; i < 10; i++)
        remove_node_last(list);

    print_list(list);

    insert_node_last(list, 99);
    print_list(list);

    delete_linked_list(list);
    return 0;
}
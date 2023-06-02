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

int insert_node_index(linked_list* list, int index, int data) {
    if (list == NULL || index < 0 || list->size < index)
        return -1;
    
    node* new_prev_node;
    node* new_next_node;

    if (index <= list->size / 2) {
        if (index == 0)
            new_prev_node = NULL;
        else
            new_prev_node = list->first;

        for (int i = 0; i < index - 1; i++) {
            new_prev_node = new_prev_node->next;
        }

        if (index == 0)
            new_next_node = list->first;
        else
            new_next_node = new_prev_node->next;
    } else {
        if (index == list->size)
            new_next_node = NULL;
        else
            new_next_node = list->last;

        for (int i = list->size - 1; i > index + 1; i--) {
            new_next_node = new_next_node->prev;
        }

        if (index == list->size)
            new_prev_node = list->last;
        else
            new_prev_node = new_next_node->prev;
    }
    
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;

    if (new_prev_node != NULL)
        new_prev_node->next = new_node;
    else
        list->first = new_node;
    new_node->prev = new_prev_node;

    if (new_next_node != NULL)
        new_next_node->prev = new_node;
    else
        list->last = new_node;
    new_node->next = new_next_node;

    list->size++;

    return 0;
}

int insert_node_first(linked_list* list, int data) {
    return insert_node_index(list, 0, data);
}

int insert_node_last(linked_list* list, int data) {
    return insert_node_index(list, list->size, data);
}

int remove_node_index(linked_list* list, int index) {
    if (list == NULL || index < 0 || list->size <= index)
        return -1;
    
    node* delete_node;

    if (index <= list->size / 2) {
        delete_node = list->first;
        for (int i = 0; i < index; i++)
            delete_node = delete_node->next;
    } else {
        delete_node = list->last;
        for (int i = list->size - 1; i > index; i--)
            delete_node = delete_node->prev;
    }
    
    node* new_prev_node = delete_node->prev;
    node* new_next_node = delete_node->next;

    if (new_prev_node != NULL)
        new_prev_node->next = new_next_node;
    else
        list->first = new_next_node;

    if (new_next_node != NULL)
        new_next_node->prev = new_prev_node;
    else
        list->last = new_prev_node;

    delete_node->prev = NULL;
    delete_node->next = NULL;
    free(delete_node);
    delete_node = NULL;
    list->size--;

    return 0;
}

int remove_node_first(linked_list* list) {
    return remove_node_index(list, 0);
}

int remove_node_last(linked_list* list) {
    return remove_node_index(list, list->size - 1);
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

int print_list_reverse(linked_list* list) {
    if (list == NULL)
        return -1;

    node* current_node = list->last;
    while (current_node != NULL) {
        printf("%d -> ", current_node->data);
        current_node = current_node->prev;
    }
    printf("NULL\n");
    return 0;
}

int print_index(linked_list* list, int index) {
    if (list == NULL || index < 0 || list->size <= index)
        return -1;
    
    node* current_node;
    if (index <= list->size / 2) {
        current_node = list->first;
        for (int i = 0; i < index; i++) {
            current_node = current_node->next;
        }
    } else {
        current_node = list->last;
        for (int i = list->size - 1; i > index; i--) {
            current_node = current_node->prev;
        }
    }
    printf("index %d: %d\n", index, current_node->data);

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

int main() {
    linked_list* list = make_linked_list();

    print_list(list);

    for (int i = 0; i < 10; i++)
        insert_node_last(list, i);
    
    print_list(list);
    print_index(list, 0);
    print_index(list, 5);
    print_index(list, 9);

    for (int i = 0; i < 10; i++)
        remove_node_last(list);

    print_list(list);

    insert_node_last(list, 99);
    print_list(list);
    remove_node_last(list);
    print_list(list);

    for (int i = 0; i < 10; i++)
        insert_node_first(list, i);

    print_list(list);

    for (int i = 0; i < 10; i++)
        remove_node_last(list);

    print_list(list);

    insert_node_index(list, -1, 0);
    insert_node_index(list, 1, 0);
    insert_node_index(list, 0, 0);
    insert_node_index(list, 0, 1);
    insert_node_index(list, 2, 2);
    insert_node_index(list, 1, 3);
    insert_node_index(list, 3, 10);
    insert_node_index(list, 1, 20);
    insert_node_index(list, 6, 100);
    insert_node_index(list, 0, 200);
    print_list(list);
    print_list_reverse(list);

    remove_node_index(list, -1);
    remove_node_index(list, 100);
    remove_node_index(list, 0);
    remove_node_index(list, 6);
    remove_node_index(list, 1);
    remove_node_index(list, 3);
    remove_node_first(list);
    remove_node_last(list);
    print_list(list);
    print_list_reverse(list);

    delete_linked_list(list);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>


typedef struct _Node {
    int value;
    struct _Node* next;
} Node;


typedef struct _LinkedList {
    int length;
    Node* head;
} LinkedList;


LinkedList* create_list(){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    Node* head = (Node*)malloc(sizeof(Node));

    head->value = 0;
    head->next = NULL;

    list->length = 0;
    list->head = head;

    return list;
}


Node* new_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}


int insert(LinkedList* list, int value, int index) {
    if (index > list->length) return -1;

    Node* node = new_node(value);

    Node* prev_node = list->head;

    for (int i = 0; i < index; i++) {
        prev_node = prev_node->next;
    }

    Node* next_node = prev_node->next;
    prev_node->next = node;
    node->next = next_node;

    list->length++;

    return 0;
}


int delete(LinkedList* list, int index) {
    if (index >= list->length) return -1;

    Node* prev_node = list->head;

    for (int i = 0; i < index - 2; i++) {
        prev_node = prev_node->next;
    }

    Node* target_node = prev_node->next;

    prev_node->next = target_node->next;
    free(target_node);

    list->length--;

    return 0;
}


void retrieve_list(LinkedList* list) {
    for(Node* node = list->head->next; node != NULL; node = node->next){
        printf("%d\n", node->value);
    }
    printf("\n");
}


int main() {
    LinkedList* list = create_list();

    insert(list, 10, 0);
    insert(list, 20, 0);
    insert(list, 30, 0);

    retrieve_list(list);

    delete(list, 0);
    retrieve_list(list);
    delete(list, 0);
    retrieve_list(list);
    delete(list, 0);
    retrieve_list(list);

    return 0;
}

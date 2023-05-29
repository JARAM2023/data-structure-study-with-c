#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 0
#define MAX 1
#define HEAP_SIZE 100

typedef struct node {
    int data;
    struct node* parent;
    struct node* left;
    struct node* right;
} node;

typedef struct heap {
    node* root;
    int mode;
    int need_leaf;
    int current_leaf;
} heap;

heap* make_heap(int mode) {
    char* mode_str;
    heap* new_heap = (heap*)malloc(sizeof(heap));
    new_heap->root = NULL;
    if (mode == MIN) {
        new_heap->mode = MIN;
        mode_str = "min";
    } else {
        new_heap->mode = MAX;
        mode_str = "max";
    }
    new_heap->need_leaf = 1;
    new_heap->current_leaf = 0;
    printf("%s heap 생성됨\n", mode_str);
    return new_heap;
}

void upheap(node* n, int mode) {
    node* current_node = n;
    while (current_node->parent != NULL
            && ((mode == MAX && current_node->parent->data < current_node->data)
                || (mode == MIN && current_node->parent->data > current_node->data))) {
        int temp = current_node->parent->data;
        current_node->parent->data = current_node->data;
        current_node->data = temp;

        current_node = current_node->parent;
    }
}

void downheap(node* n, int mode) {
    node* current_node = n;
    if (current_node == NULL)
        return;

    while (current_node->left != NULL) {
        if (current_node->left != NULL && current_node->right != NULL) {
            if ((mode == MAX && current_node->left->data >= current_node->right->data && current_node->left->data > current_node->data)
                || (mode == MIN && current_node->left->data <= current_node->right->data && current_node->left->data < current_node->data)) {
                int temp = current_node->left->data;
                current_node->left->data = current_node->data;
                current_node->data = temp;
                current_node = current_node->left;
            } else if ((mode == MAX && current_node->right->data >= current_node->left->data && current_node->right->data > current_node->data)
                        || (mode == MIN && current_node->right->data <= current_node->left->data && current_node->right->data < current_node->data)) {
                int temp = current_node->right->data;
                current_node->right->data = current_node->data;
                current_node->data = temp;
                current_node = current_node->right;
            } else
                break;
        } else if (current_node->left != NULL) {
            if ((mode == MAX && current_node->left->data > current_node->data)
                || (mode == MIN && current_node->left->data < current_node->data)) {
                int temp = current_node->left->data;
                current_node->left->data = current_node->data;
                current_node->data = temp;
                current_node = current_node->left;
            } else
                break;
        }
    }
}

int insert_node(heap* h, int data) {
    if (h == NULL) {
        printf("heap이 없음\n");
        return -1;
    }

    node* current_node = h->root;
    node* parent_node = NULL;

    int need_leaf = h->need_leaf;
    int current_leaf = h->current_leaf;
    int is_left = 0;

    while (need_leaf != 1) {
        parent_node = current_node;
        if ((need_leaf >>= 1) > current_leaf) {
            current_node = current_node->left;
            is_left = 1;
        } else {
            current_leaf -= need_leaf;
            current_node = current_node->right;
            is_left = 0;
        }
    }

    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->parent = parent_node;
    new_node->left = NULL;
    new_node->right = NULL;

    if (parent_node != NULL) {
        if (is_left)
            parent_node->left = new_node;
        else
            parent_node->right = new_node;
    } else
        h->root = new_node;

    (h->current_leaf)++;
    if (h->need_leaf == h->current_leaf) {
        h->need_leaf <<= 1;
        h->current_leaf = 0;
    }

    upheap(new_node, h->mode);

    return data;
}

int remove_node(heap* h) {
    if (h == NULL || h->root == NULL) {
        printf("heap이 없거나 삭제할 노드가 없음\n");
        return -1;
    }

    int data = h->root->data;

    (h->current_leaf)--;
    if (h->current_leaf == -1) {
        h->need_leaf >>= 1;
        h->current_leaf = h->need_leaf - 1;
    }

    node* current_node = h->root;
    node* parent_node = NULL;

    int need_leaf = h->need_leaf;
    int current_leaf = h->current_leaf;
    int is_left = 0;

    while (need_leaf != 1) {
        parent_node = current_node;
        if ((need_leaf >>= 1) > current_leaf) {
            current_node = current_node->left;
            is_left = 1;
        } else {
            current_leaf -= need_leaf;
            current_node = current_node->right;
            is_left = 0;
        }
    }

    h->root->data = current_node->data;

    current_node->parent = NULL;
    current_node->left = NULL;
    current_node->right = NULL;
    free(current_node);
    current_node = NULL;

    if (parent_node != NULL) {
        if (is_left)
            parent_node->left = NULL;
        else
            parent_node->right = NULL;
    } else
        h->root = NULL;
    
    downheap(h->root, h->mode);

    return data;
}

void destroy_heap(heap** h) {
    char* mode_str;
    if ((*h)->mode == MAX)
        mode_str = "max";
    else
        mode_str = "min";

    while ((*h)->root != NULL) {
        int data = remove_node(*h);
        printf("%s heap 삭제 중... 현재 root 값: %d\n", mode_str, data);
    }

    free(*h);
    *h = NULL;
    printf("%s heap 삭제 완료\n", mode_str);
}

typedef struct heap_arr {
    int datas[HEAP_SIZE];
    int index;
    int mode;
} heap_arr;

heap_arr* make_heap_arr(int mode) {
    char* mode_str;
    heap_arr* new_heap_arr = (heap_arr*)malloc(sizeof(heap_arr));
    new_heap_arr->index = 0;
    if (mode == MIN) {
        new_heap_arr->mode = MIN;
        mode_str = "min";
    } else {
        new_heap_arr->mode = MAX;
        mode_str = "max";
    }
    printf("%s heap arr 생성됨\n", mode_str);
    return new_heap_arr;
}

void upheap_arr(heap_arr* h, int mode) {
    int index = h->index;
    while (index != 0) {
        int parent_index = index / 2;
        if (index % 2 == 0)
            parent_index -= 1;
        
        if ((mode == MAX && h->datas[parent_index] < h->datas[index])
            || (mode == MIN && h->datas[parent_index] > h->datas[index])) {
            int temp = h->datas[parent_index];
            h->datas[parent_index] = h->datas[index];
            h->datas[index] = temp;
            index = parent_index;
        } else
            break;
    }
}

void downheap_arr(heap_arr* h, int mode) {
    int index = 0;
    while ((index * 2 + 1) < h->index) {
        int left_index = index * 2 + 1;
        int right_index = index * 2 + 2;

        if (left_index < h->index && right_index < h->index) {
            if ((mode == MAX && h->datas[left_index] >= h->datas[right_index] && h->datas[left_index] > h->datas[index])
                || (mode == MIN && h->datas[left_index] <= h->datas[right_index] && h->datas[left_index] < h->datas[index])) {
                int temp = h->datas[left_index];
                h->datas[left_index] = h->datas[index];
                h->datas[index] = temp;
                index = left_index;
            } else if ((mode == MAX && h->datas[right_index] >= h->datas[left_index] && h->datas[right_index] > h->datas[index])
                        || (mode == MIN && h->datas[right_index] <= h->datas[left_index] && h->datas[right_index] < h->datas[index])) {
                int temp = h->datas[right_index];
                h->datas[right_index] = h->datas[index];
                h->datas[index] = temp;
                index = right_index;
            } else
                break;
        } else if (left_index < h->index) {
            if ((mode == MAX && h->datas[left_index] > h->datas[index])
                || (mode == MIN && h->datas[left_index] < h->datas[index])) {
                int temp = h->datas[left_index];
                h->datas[left_index] = h->datas[index];
                h->datas[index] = temp;
                index = left_index;
            } else
                break;
        }
    }
}

int insert_value_arr(heap_arr* h, int data) {
    if (h == NULL) {
        printf("heap arr가 없음\n");
        return -1;
    }

    if (h->index == HEAP_SIZE) {
        printf("heap arr가 꽉 참\n");
        return -1;
    }

    h->datas[h->index] = data;
    upheap_arr(h, h->mode);
    (h->index)++;
    return data;
}

int remove_value_arr(heap_arr* h) {
    if (h == NULL || h->index == 0) {
        printf("heap arr가 없거나 삭제할 값이 없음\n");
        return -1;
    }

    int data = h->datas[0];
    h->datas[0] = h->datas[--(h->index)];
    downheap_arr(h, h->mode);
    return data;
}

void destroy_heap_arr(heap_arr** h) {
    char* mode_str;
    if ((*h)->mode == MAX)
        mode_str = "max";
    else
        mode_str = "min";

    while ((*h)->index != 0) {
        int data = remove_value_arr(*h);
        printf("%s heap arr 삭제 중... 현재 root 값: %d\n", mode_str, data);
    }

    free(*h);
    *h = NULL;
    printf("%s heap arr 삭제 완료\n", mode_str);
}

int main() {
    srand(time(NULL));

    // 구조체로 구현(동적)
    heap* max_heap = make_heap(MAX);
    heap* min_heap = make_heap(MIN);

    remove_node(max_heap);
    remove_node(min_heap);

    for (int i = 0; i < 100; i++)
        printf("max heap에 삽입됨: %d\n", insert_node(max_heap, (rand() % 100) + 1));
    
    for (int i = 0; i < 100; i++)
        printf("min heap에 삽입됨: %d\n", insert_node(min_heap, (rand() % 100) + 1));

    for (int i = 0; i < 10; i++)
        printf("max heap의 root 값: %d\n", remove_node(max_heap));
    
    for (int i = 0; i < 10; i++)
        printf("min heap의 root 값: %d\n", remove_node(min_heap));
    
    destroy_heap(&max_heap);
    destroy_heap(&min_heap);

    // 배열로 구현(정적)
    heap_arr* max_heap_arr = make_heap_arr(MAX);
    heap_arr* min_heap_arr = make_heap_arr(MIN);

    remove_value_arr(max_heap_arr);
    remove_value_arr(min_heap_arr);

    for (int i = 0; i < 100; i++)
        printf("max heap arr에 삽입됨: %d\n", insert_value_arr(max_heap_arr, (rand() % 100) + 1));
    
    for (int i = 0; i < 100; i++)
        printf("min heap arr에 삽입됨: %d\n", insert_value_arr(min_heap_arr, (rand() % 100) + 1));
    
    insert_value_arr(max_heap_arr, (rand() % 100) + 1);
    insert_value_arr(min_heap_arr, (rand() % 100) + 1);

    for (int i = 0; i < 10; i++)
        printf("max heap arr의 root 값: %d\n", remove_value_arr(max_heap_arr));
    
    for (int i = 0; i < 10; i++)
        printf("min heap arr의 root 값: %d\n", remove_value_arr(min_heap_arr));

    destroy_heap_arr(&max_heap_arr);
    destroy_heap_arr(&min_heap_arr);
    return 0;
}
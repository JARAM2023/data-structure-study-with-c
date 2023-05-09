#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TEST_COUNT 100
#define RANDOM_RANGE 1000

typedef struct binary_tree {
    int data;
    struct binary_tree* left;
    struct binary_tree* right;
} binary_tree;

binary_tree* make_binary_tree(int data) {
    binary_tree* b = (binary_tree*)malloc(sizeof(binary_tree));
    b->data = data;
    b->left = NULL;
    b->right = NULL;

    return b;
}

binary_tree* inorder_predecessor(binary_tree* b) {
    if (b == NULL)
        return NULL;

    binary_tree* current_node = b->left;
    if (current_node != NULL) {
        while (current_node->right != NULL)
            current_node = current_node->right;
    }

    return current_node;
}

binary_tree* inorder_successor(binary_tree* b) {
    if (b == NULL)
        return NULL;

    binary_tree* current_node = b->right;
    if (current_node != NULL) {
        while (current_node->left != NULL)
            current_node = current_node->left;
    }

    return current_node;
}

void insert_node(binary_tree* b, int data) {
    if (b == NULL)
        return;

    binary_tree* current_node = b;
    binary_tree* parent_node = NULL;
    int is_left = 0;

    while (current_node != NULL) {
        parent_node = current_node;
        if (data < current_node->data) {
            current_node = current_node->left;
            is_left = 1;
        } else if (data > current_node->data) {
            current_node = current_node->right;
            is_left = 0;
        } else {
            printf("이미 %d이(가) 존재하여 삽입 거부\n");
            return;
        }
    }

    current_node = (binary_tree*)malloc(sizeof(binary_tree));
    
    if (is_left)
        parent_node->left = current_node;
    else
        parent_node->right = current_node;

    current_node->data = data;
    current_node->left = NULL;
    current_node->right = NULL;
}

int search_data(binary_tree* b, int data) {
    if (b == NULL) {
        printf("%d이 없음\n", data);
        return -1;
    }

    binary_tree* current_node = b;
    int depth = 0;

    while (current_node != NULL) {
        if (data == current_node->data) {
            printf("%d을(를) 찾음\n", data);
            return depth;
        }

        if (data < current_node->data)
            current_node = current_node->left;
        else
            current_node = current_node->right;
        depth++;
    }

    printf("%d이 없음\n", data);
    return -1;
}

void delete_node(binary_tree** b, int data) {
    if (*b == NULL) {
        printf("삭제할 %d이 없음\n", data);
        return;
    }
    
    binary_tree* current_node = *b;
    binary_tree* parent_node = NULL;
    int is_left = 0;

    while (current_node != NULL) {
        if (data == current_node->data)
            break;
        
        parent_node = current_node;

        if (data < current_node->data) {
            current_node = current_node->left;
            is_left = 1;
        } else {
            current_node = current_node->right;
            is_left = 0;
        }
    }

    if (current_node == NULL) {
        printf("삭제할 %d이 없음\n", data);
        return;
    }

    if (current_node->left == NULL) {
        if (parent_node == NULL)
            *b = current_node->right;
        else {
            if (is_left)
                parent_node->left = current_node->right;
            else
                parent_node->right = current_node->right;
        }

        current_node->left = NULL;
        current_node->right = NULL;
        free(current_node);
        current_node = NULL;
    } else if (current_node->right == NULL) {
        if (parent_node == NULL)
            *b = current_node->left;
        else {
            if (is_left)
                parent_node->left = current_node->left;
            else
                parent_node->right = current_node->left;
        }

        current_node->left = NULL;
        current_node->right = NULL;
        free(current_node);
        current_node = NULL;
    } else {
        binary_tree* inorder_predecessor_node = inorder_predecessor(current_node);
        binary_tree* inorder_successor_node = inorder_successor(current_node);
        int inorder_predecessor_data = inorder_predecessor_node->data;
        int inorder_successor_data = inorder_successor_node->data;

        int inorder_predecessor_depth = search_data(*b, inorder_predecessor_data);
        int inorder_successor_depth = search_data(*b, inorder_successor_data);

        // depth가 더 큰 부분의 노드를 지워 height를 낮추는 방향으로 지우기
        if (inorder_predecessor_depth >= inorder_successor_depth) {
            delete_node(b, inorder_predecessor_data);
            current_node->data = inorder_predecessor_data;
        } else {
            delete_node(b, inorder_successor_data);
            current_node->data = inorder_successor_data;
        }
    }
}

void inorder(binary_tree* b) {
    if (b != NULL) {
        inorder(b->left);
        printf("%d ", b->data);
        inorder(b->right);
    }
}

void preorder(binary_tree* b) {
    if (b != NULL) {
        printf("%d ", b->data);
        preorder(b->left);
        preorder(b->right);
    }
}

void postorder(binary_tree* b) {
    if (b != NULL) {
        postorder(b->left);
        postorder(b->right);
        printf("%d ", b->data);
    }
}

void destroy_binary_tree(binary_tree** b) {
    if (*b != NULL) {
        destroy_binary_tree(&((*b)->left));
        destroy_binary_tree(&((*b)->right));
        (*b)->left = NULL;
        (*b)->right = NULL;
        free(*b);
        *b = NULL;
    }
}

int main() {
    srand(time(NULL));

    int datas[TEST_COUNT];
    for (int i = 0; i < TEST_COUNT; i++)
        datas[i] = (rand() % RANDOM_RANGE) + 1;

    binary_tree* root = make_binary_tree(datas[0]);
    for (int i = 0; i < TEST_COUNT; i++)
        insert_node(root, datas[i]);

    for (int i = 0; i < TEST_COUNT; i++) {
        // search_data 함수는 해당 노드의 depth를 반환하게 구현함
        printf("%d의 depth: %d\n", datas[i], search_data(root, datas[i]));
    }
    
    printf("Preorder: ");
    preorder(root);
    printf("\n");
    printf("Inorder: ");
    inorder(root);
    printf("\n");
    printf("Postorder: ");
    postorder(root);
    printf("\n");

    binary_tree* inorder_predecessor_node = inorder_predecessor(root);
    binary_tree* inorder_successor_node = inorder_successor(root);

    if (inorder_predecessor_node == NULL)
        printf("inorder predecessor: NULL\n");
    else
        printf("inorder predecessor: %d\n", inorder_predecessor_node->data);

    if (inorder_successor_node == NULL)
        printf("inorder successor: NULL\n");
    else
        printf("inorder successor: %d\n", inorder_successor_node->data);

    for (int i = TEST_COUNT - 1; i >= 0; i--)
        delete_node(&root, datas[i]);
    
    if (root == NULL)
        printf("BST 모두 삭제됨\n");
    
    // ----------------------------------------------------------------------------------------------------

    root = make_binary_tree(datas[0]);
    for (int i = 0; i < TEST_COUNT; i++)
        insert_node(root, datas[i]);

    destroy_binary_tree(&root);
    if (root == NULL)
        printf("BST 모두 삭제됨\n");

    return 0;
}
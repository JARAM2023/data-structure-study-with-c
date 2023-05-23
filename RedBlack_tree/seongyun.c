#include <stdio.h>
#include <stdlib.h>

// Red-Black Tree의 노드 구조체 정의
typedef struct Node {
    int key;
    int color; // 0: black, 1: red
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// 전역 변수로 트리의 루트 노드 선언
Node* root = NULL;

// 삽입 연산을 위한 보조 함수
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = 1; // 새로운 노드는 항상 빨간색으로 삽입됨
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

Node* bstInsert(Node* root, Node* newNode) {
    if (root == NULL) return newNode;

    if (newNode->key < root->key) {
        root->left = bstInsert(root->left, newNode);
        root->left->parent = root;
    }
    else if (newNode->key > root->key) {
        root->right = bstInsert(root->right, newNode);
        root->right->parent = root;
    }

    return root;
}

// 회전 연산을 위한 보조 함수
void leftRotate(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != NULL)
        rightChild->left->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == NULL)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void rightRotate(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != NULL)
        leftChild->right->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == NULL)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

// 삽입 후 재조정을 위한 보조 함수
void fixInsert(Node* node) {
    while (node != root && node->parent->color == 1) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }

                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotate(node->parent->parent);
            }
        }
        else {
            Node* uncle = node->parent->parent->left;

            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }

                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotate(node->parent->parent);
            }
        }
    }

    root->color = 0; // 루트 노드는 항상 검은색
}

// 삽입 연산 함수
void insert(int key) {
    Node* newNode = createNode(key);
    root = bstInsert(root, newNode);
    fixInsert(newNode);
}

// 탐색 연산 함수
Node* search(int key) {
    Node* current = root;
    while (current != NULL && current->key != key) {
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

// 트리를 중위 순회하여 출력하는 함수
void inorderTraversal(Node* node) {
    if (node == NULL) return;
    inorderTraversal(node->left);
    printf("%d ", node->key);
    inorderTraversal(node->right);
}

// 메모리 해제를 위한 후위 순회 함수
void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// 테스트를 위한 예시 코드
int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    Node* result1 = search(30);
    if (result1 != NULL)
        printf("Key 30 found in the tree.\n");
    else
        printf("Key 30 not found in the tree.\n");

    Node* result2 = search(1);
    if (result2 != NULL)
        printf("Key 1 found in the tree.\n");
    else
        printf("Key 1 not found in the tree.\n");

    freeTree(root);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int key;
    enum Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;
struct Node* NIL = NULL; // NIL 노드

// 도우미 함수: 새로운 노드 생성
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = RED;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 도우미 함수: 노드의 색상 반환 (NIL 노드는 BLACK으로 처리)
enum Color getColor(struct Node* node) {
    if (node == NULL || node == NIL)
        return BLACK;
    else
        return node->color;
}

// 도우미 함수: 노드의 색상 변경
void setColor(struct Node* node, enum Color color) {
    if (node != NULL && node != NIL)
        node->color = color;
}

// 도우미 함수: 노드의 부모 노드 반환
struct Node* getParent(struct Node* node) {
    if (node == NULL || node == NIL)
        return NULL;
    else
        return node->parent;
}

// 도우미 함수: 노드의 형제 노드 반환
struct Node* getSibling(struct Node* node) {
    struct Node* parent = getParent(node);
    if (parent == NULL)
        return NULL;
    if (node == parent->left)
        return parent->right;
    else
        return parent->left;
}

// 도우미 함수: 노드를 부모의 왼쪽 자식으로 설정
void setAsLeftChild(struct Node* parent, struct Node* child) {
    parent->left = child;
    if (child != NULL)
        child->parent = parent;
}

// 도우미 함수: 노드를 부모의 오른쪽 자식으로 설정
void setAsRightChild(struct Node* parent, struct Node* child) {
    parent->right = child;
    if (child != NULL)
        child->parent = parent;
}

// 도우미 함수: 노드 삽입 후 균형 잡기
void insertFixup(struct Node* node) {
    while (node->parent != NULL && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            struct Node* uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        } else {
            struct Node* uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// 도우미 함수: 노드 왼쪽으로 회전
void rotateLeft(struct Node* node) {
    struct Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != NIL)
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

// 도우미 함수: 노드 오른쪽으로 회전
void rotateRight(struct Node* node) {
    struct Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != NIL)
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

// 노드 삽입
void insert(int key) {
    struct Node* newNode = createNode(key);
    struct Node* current = root;
    struct Node* parent = NULL;
    while (current != NIL) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else {
            printf("중복된 키는 삽입할 수 없습니다.\n");
            free(newNode);
            return;
        }
    }
    newNode->parent = parent;
    if (parent == NULL)
        root = newNode;
    else if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->color = RED;
    insertFixup(newNode);
}

// 중위 순회
void inorderTraversal(struct Node* node) {
    if (node != NULL && node != NIL) {
        inorderTraversal(node->left);
        printf("%d ", node->key);
        inorderTraversal(node->right);
    }
}

int main() {
    NIL = (struct Node*)malloc(sizeof(struct Node));
    NIL->color = BLACK;
    root = NIL;

    insert(7);
    insert(3);
    insert(18);
    insert(10);
    insert(22);
    insert(8);
    insert(11);
    insert(26);
    insert(2);
    insert(6);
    insert(13);

    printf("트리 : ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// 이진 트리 구조체
typedef struct node {
    int data;           // 노드의 데이터
    struct node* left;  // 왼쪽 자식 노드
    struct node* right; // 오른쪽 자식 노드
} Node;

// 이진 탐색 트리 구조체
typedef struct bst {
    Node* root; // 루트 노드
} BST;

Node* find_min_node(Node* node);

// 새로운 노드 생성 함수
Node* create_node(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 이진 탐색 트리에 노드 삽입 함수
void insert_node(BST* bst, int data) {
    Node* new_node = create_node(data);
    Node* curr_node = bst->root;
    Node* parent_node = NULL;
    
    // 삽입할 위치 탐색
    while (curr_node != NULL) {
        parent_node = curr_node;
        if (data < curr_node->data) {
            curr_node = curr_node->left;
        } else {
            curr_node = curr_node->right;
        }
    }
    
    // 삽입할 위치에 노드 삽입
    // root노드에 추가
    if (parent_node == NULL) {
        bst->root = new_node;
    } else if (data < parent_node->data) {
        parent_node->left = new_node;
    } else {
        parent_node->right = new_node;
    }
}

// 이진 트리 전위 순회 함수
void preorder(Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

// 이진 트리 중위 순회 함수
void inorder(Node* node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// 이진 트리 후위 순회 함수
void postorder(Node* node) {
    if (node == NULL) return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

// 이진 트리에서 특정 노드를 제거하는 함수
Node* remove_node(Node* root, int data) {
    if (root == NULL) return root;

    // 제거할 노드가 현재 노드보다 작으면 왼쪽 서브트리에서 제거할 노드를 찾습니다.
    if (data < root->data) {
        root->left = remove_node(root->left, data);
    }
    // 제거할 노드가 현재 노드보다 크면 오른쪽 서브트리에서 제거할 노드를 찾습니다.
    else if (data > root->data) {
        root->right = remove_node(root->right, data);
    }
    // 제거할 노드를 찾았을 경우
    else {
        // 제거할 노드가 리프 노드인 경우
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        // 제거할 노드가 자식 노드를 한 개 갖는 경우
        else if (root->left == NULL) {
            // 현재 노드의 부모노드가 자식노드를 가르키게끔 만듬
            Node* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) {
            Node* temp = root;
            root = root->left;
            free(temp);
        }
        // 제거할 노드가 자식 노드를 두 개 갖는 경우
        else {
            Node* temp = find_min_node(root->right);
            root->data = temp->data;
            root->right = remove_node(root->right, temp->data);
        }
    }
    return root;
}

// 오른쪽 서브트리에서 가장 작은 값을 갖는 노드를 찾는 함수
Node* find_min_node(Node* node) {
    Node* curr_node = node;
    while (curr_node->left != NULL) {
        curr_node = curr_node->left;
    }
    return curr_node;
}


int main() {
    BST bst;
    bst.root = NULL;
    
    // 이진 탐색 트리에 노드 삽입
    insert_node(&bst, 50);
    insert_node(&bst, 30);
    insert_node(&bst, 20);
    insert_node(&bst, 40);
    insert_node(&bst, 70);
    insert_node(&bst, 60);
    insert_node(&bst, 80);

    // 이진 트리 순회
    printf("Preorder traversal: ");
    preorder(bst.root);
    printf("\n");

    printf("Inorder traversal: ");
    inorder(bst.root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(bst.root);
    printf("\n");

    return 0;
}

// B-tree 삽입, 탐색, 삭제는 몰루겟어요 ㅠ
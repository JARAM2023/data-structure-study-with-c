/*
    binary_tree의 한 종류
    Root(Black), NIL(Black)
    Red의 자식 = Black,     Black의 자식은 상관X
    무작위Node ~ NIL까지 같은수의 Black Node(자신 제외)
*/
/*
    삽입시 red로 삽입(black Height를 맟추기 위해)
    부모와 자식간 색깔 한번에 바꿔도 된다(위의 규칙에 위배만 안되면)
*/
#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

typedef struct Node {
    int key;
    enum Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;
// 자녀가 2개인 노드u가 delete시에 삭제되는 u에 자리에 successor v(minValueNode를 통해 찾은)를 넣고
// 삭제할 u를 바로 지울수 있게한다 대신 색깔은 바뀌지 않는다.
void transplant(Node** root, Node* u, Node* v) {
    // u is Root    u = v
    if (u->parent == NULL)
        *root = v;
    // u is left    u = v
    else if (u == u->parent->left)
        u->parent->left = v;
    // u is right   u = v
    else
        u->parent->right = v;
    // v = u
    if (v != NULL)
        v->parent = u->parent;
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = RED;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/*
P       X
 X  -> P Y
  Y
*/
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;

    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}
/*
  P     X
 X  -> Y P
Y
*/
void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}
// leftRotate나 rightRotate가 필요할때 사용-이때 잘 몰루
void insertFixup(Node** root, Node* node) {
    while (node != *root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* y = node->parent->parent->right;
            if (y != NULL && y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root, node->parent->parent);
            }
        } else {
            Node* y = node->parent->parent->left;
            if (y != NULL && y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(root, node->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}
// 일단 leaf노드에 삽입
void insert(Node** root, int key) {
    Node* node = createNode(key);
    Node* y = NULL;
    Node* x = *root;

    while (x != NULL) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y == NULL)
        *root = node;
    else if (node->key < y->key)
        y->left = node;
    else
        y->right = node;
    // 여기서 binary 규칙에 맟춘다
    insertFixup(root, node);
}
// Delete시에 찾는함수
Node* search(Node* root, int key) {
    while (root != NULL && key != root->key) {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}
// Delete시 이용
Node* minValueNode(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}
/* leftRotate나 rightRotate가 필요할때 사용-이때 잘 몰루
 red & (extra)black -> black
 double black의 경우 
      B                                                                             D
   A(BB) D(B)   인 경우에 E의 red를 A의 B한개와 바꿔 R&B해결,   바꾸는 과정은 rotation이용  B(R&B)  E(B)    형태가 된다
        C E(R)                                                               A(B) C
*/
void deleteFixup(Node** root, Node* node, Node* parent) {
    Node* sibling;
    while ((node == NULL || node->color == BLACK) && node != *root) {
        if (node == parent->left) {
            sibling = parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                leftRotate(root, parent);
                sibling = parent->right;
            }
            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(root, sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(root, parent);
                node = *root;
                break;
            }
        } else {
            sibling = parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rightRotate(root, parent);
                sibling = parent->left;
            }
            if ((sibling->right == NULL || sibling->right->color == BLACK) &&
                (sibling->left == NULL || sibling->left->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(root, sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(root, parent);
                node = *root;
                break;
            }
        }
    }
    if (node != NULL)
        node->color = BLACK;
}
// red지우는건 상관X,   black지우면 그 자리에 extra black 추가
void deleteNode(Node** root, int key) {
    Node* z = search(*root, key);
    if (z == NULL)
        return;

    Node* y = z;
    Node* x;
    enum Color originalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minValueNode(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (originalColor == BLACK)
        deleteFixup(root, x, y->parent);

    free(z);
}

void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->key);
        inorderTraversal(node->right);
    }
}




int main() {
    Node* root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    deleteNode(&root, 20);

    printf("Inorder traversal after deletion: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
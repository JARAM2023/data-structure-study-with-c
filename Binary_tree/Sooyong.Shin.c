#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node *root;

Node *insertNode(Node *ptr, int num);
Node *deleteNode(Node *ptr, int num);
int maxDepth(Node* node);
void printTree(Node *node, int level);

int main() {
	int tmpList[20];
	int tmp;

	srand(time(NULL));

	root = insertNode(root, rand() % 100);

	for (int i = 1; i < 20; i++) {
		tmp = rand() % 100;
		insertNode(root, tmp);
		tmpList[i-1] = tmp;
	}

	printTree(root, 0);

	for (int i = 0; i < 5; i++) {
		deleteNode(root, tmpList[rand()%20]);
		// printDft(root);
	}
	printTree(root, 0);

}

Node *newNode(int num) {
	Node *new = (Node*)malloc(sizeof(Node));
	new -> data = num;
	new -> left = NULL;
	new -> right = NULL;

	return new;
}

Node *insertNode(Node *ptr, int num) {
	if (ptr == NULL)
		return newNode(num);

	if (ptr -> data > num)
		ptr -> left = insertNode(ptr -> left, num);
	else if (ptr -> data < num)
		ptr -> right = insertNode(ptr -> right, num);
	else
		printf("Already exist\n");

	return ptr;
}

Node* deleteNode(Node *ptr, int num) {
    if (ptr == NULL) {
        return ptr;
    }

    if (num < ptr -> data) {
        ptr -> left = deleteNode(ptr -> left, num);
    } else if (num > ptr -> data) {
        ptr -> right = deleteNode(ptr -> right, num);
    } else {
        if (ptr -> left == NULL) {
            struct Node* tmp = ptr -> right;
            free(ptr);

            return tmp;
        } else if (ptr -> right == NULL) {
            struct Node* tmp = ptr -> left;
            free(ptr);

            return tmp;
        }

        Node* minNode = ptr -> right;

        while(minNode -> left != NULL)
        	minNode = minNode -> left;

        Node* tmp = minNode;
        ptr -> data = tmp -> data;
        ptr -> right = deleteNode(ptr -> right, tmp -> data);
    }

    return ptr;
}

int maxDepth(Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        if (leftDepth > rightDepth) {
            return (leftDepth + 1);
        } else {
            return (rightDepth + 1);
        }
    }
}

void printTree(Node *node, int level) {
    if (node == NULL) {
        return;
    }
    // 현재 노드 출력
    printf("%*s", level*4, ""); // 들여쓰기
    printf("%d\n", node->data);
    // 자식 노드들 출력
    printTree(node->left, level+1);
    printTree(node->right, level+1);
}
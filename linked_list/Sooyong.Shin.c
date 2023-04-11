#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
		int data;
		struct Node *next;
} Node;

Node* createNode(int i);
int insertNode(int i);
int removeNodeIdx(int i);
void printList();

Node *head;

int main () {
		for (int i = 1; i < 11; i++) insertNode(i);

		printList();

		removeNodeIdx(3);
		removeNodeIdx(6);
		removeNodeIdx(9);

		printList();

		return 0;
}

Node* createNode (int i) {
		Node *newNode = (Node*)malloc(sizeof(Node));

		newNode -> data = i;
		newNode -> next = NULL;

		return newNode;
}

int insertNode (int i) {
		if (head == NULL) {
				head = createNode(i);
				return i;
		}

		Node *curptr = head;

		while(curptr -> next != NULL)
				curptr = curptr -> next;

		curptr -> next = createNode(i);

		return i;
}

int removeNodeIdx (int i) {
		int removedData;
		Node* prevNode=head;
		Node* targetNode;

		if (i == 1) {
				targetNode = head;
				head = head -> next;
				removedData = targetNode -> data;
				free(targetNode);
				return removedData;
		}

		for (; i != 2; i--) { 
				if (prevNode -> next != NULL) {
						prevNode = prevNode -> next; 
				} else {
						printf("Wrong index\n");
						return -1;
				}
		}

		targetNode = prevNode -> next;

		removedData = targetNode -> data;
		prevNode -> next = targetNode -> next;
		free(targetNode);

		return removedData;
}

void printList() {
		Node *curptr = head;
		
		printf("Print start\n");

		while (curptr != NULL) {
				printf("%d -> ", curptr -> data);
				curptr = curptr -> next;
		}

		printf("\n");
}

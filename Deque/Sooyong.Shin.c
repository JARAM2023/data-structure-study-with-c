#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node *head;
Node *tail;

int putAhead(int num);
int getAhead();
int putBehind(int num);
int getBehind();
void printDeque();

int main () {
	for (int i = 0; i < 30; i++)
		if (i % 2 == 0)
			printf("Put Ahead %d to Deque\n", putAhead(i));
		else
			printf("Put Behind %d to Deque\n", putBehind(i));

	printDeque();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++)
			printf("Get Ahead %d from Deque\n", getAhead());
		printDeque();

		for (int j = 0; j < 5; j++)
			printf("Get Behind %d from Deque\n", getBehind());
		printDeque();
	}

	return 0;
}

int putAhead(int num) {
	if (head == NULL) {
		head = (Node*)malloc(sizeof(Node));
		head -> data = num;
		tail = head;
		return num;
	} 

	Node *tmpNode = (Node*)malloc(sizeof(Node));
	tmpNode -> next = head;
	tmpNode -> data = num;
	head = tmpNode;

	return num;
}

int getAhead() {
	int tmp = head -> data;

	if (head == tail) {
		head = NULL;
		return tmp;
	}

	Node *tmpNode = head;
	head = head -> next;
	free(tmpNode);

	return tmp;
}

int putBehind(int num) {
	if (head == NULL) {
		head = (Node*)malloc(sizeof(Node));
		head -> data = num;
		tail = head;
		return num;
	} else if (head == tail) {
		head -> next = (Node*)malloc(sizeof(Node));
		tail = head -> next;
		tail -> data = num;
		return num;
	}

	tail -> next = (Node*)malloc(sizeof(Node));
	tail = tail -> next;
	tail -> data = num;

	return num;
}

int getBehind() {
	int tmp = tail -> data;

	if (head == tail) {
		head = NULL;
		return tmp;
	}

	Node *tmpNode = head;

	while (tmpNode -> next != tail)
		tmpNode = tmpNode -> next;

	free(tail);
	tail = tmpNode;

	return tmp;
}

void printDeque () {
	if (head == NULL) {
		printf("Null Queue\n");
		return;
	}

	Node *ptrNode = head;

	printf("Head ");
	while (ptrNode != tail) {
		printf("%d -> ", ptrNode -> data);
		ptrNode = ptrNode -> next;
	}

	printf("%d Tail\nEnd print\n", ptrNode -> data);
}
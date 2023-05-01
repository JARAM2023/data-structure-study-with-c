#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node *head;
Node *tail;

int put(int num);
int get();
void printQueue();

int main () {
	for (int i = 0; i < 33; i++)
		printf("Put %d to Queue\n", put(i));

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++)
			printf("Get %d from Queue\n", get());

		printQueue();
	}

	return 0;
}

int put (int num) {
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

int get () {
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

void printQueue () {
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

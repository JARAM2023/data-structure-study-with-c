#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node *top;

int push (int num);
int pop ();

int main () {
	for (int i = 0; i < 30; i++)
		printf("Push %d to stack\n", push(i));

	for (int i = 0; i < 30; i++)
		printf("%d popped from stack\n", pop());

	return 0;
}

int push (int num) {
	if (top == NULL) {
		top = (Node*)malloc(sizeof(Node));
		top -> data = num;
		return num;
	}

	Node *new = (Node*)malloc(sizeof(Node));
	new -> data = num;
	new -> next = top;
	top = new;

	return num;
}

int pop () {
	int tmp = top -> data;

	if (top -> next != NULL) {
		Node *tmpNode = top;
		top = top -> next;
		free(tmpNode);	
	} else {
		top = NULL;
	}

	return tmp;
}

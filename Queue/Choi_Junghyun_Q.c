// FIFO     enqueue(추가) dequeue(꺼내기)
// front와 rear 둘다 필요
#include <stdio.h>

int queue[100];
int front = 0;
int rear = -1;

void enqueue(int data) {
    if (rear >= 100 - 1) {
        printf("오버플로\n");
        return;
    }
    queue[++rear] = data;
}

int dequeue() {
    if (front > rear) {
        printf("arr is empty!\n");
        return -1;
    }
    return queue[front++];
}

int main() {
    enqueue(9);
    enqueue(2);
    enqueue(7);
    enqueue(3);
    printf("%d\n", dequeue());  // 9
    printf("%d\n", dequeue());  // 2
    printf("%d\n", dequeue());  // 7
    printf("%d\n", dequeue());  // 3
    printf("%d\n", dequeue());  // arr is empty!
    return 0;
}

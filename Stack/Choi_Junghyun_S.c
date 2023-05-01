// LIFO push(넣기) pop(꺼내기)  중간삽입.삭제 불가
// top은 제일 위에(최근에 push한 값)

#include <stdio.h>

int stack[100];
int top = -1;

void push(int data) {
    if (top >= 100 - 1) {
        printf("오버플로\n");
        return;
    }
    stack[++top] = data;
}

int pop() {
    if (top < 0) {
        printf("arr is empty\n");
        return -1; // 비어있을 때 보통 index를 -1(불가능한)return 한다
    }
    return stack[top--];
}

int main() {
    push(1);
    push(7);
    push(2);
    push(9);
    printf("%d\n", pop());  // 9
    printf("%d\n", pop());  // 2
    printf("%d\n", pop());  // 7
    printf("%d\n", pop());  // 1
    printf("%d\n", pop());  // arr is empty
    return 0;
}

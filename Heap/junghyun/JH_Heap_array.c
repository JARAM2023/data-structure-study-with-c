#include <stdio.h>
#include <stdlib.h>
// 배열로 구한 heap
#define MAX_HEAP_SIZE 100
// min_heap형태로 root가 min값을 가지는 구조를 
typedef struct {
    int heap[MAX_HEAP_SIZE];
    int size;   // heap[size - 1] = last_node
} MinHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
// insert시에 부모-자식간 대소관계 다르면 사용
// binary라서 밑의 관계로 index작용
// childIndex = index
// parentIndex = (index - 1) / 2
void upheap(MinHeap* minHeap, int index) {
    if (index <= 0) {
        return;
    }

    int parentIndex = (index - 1) / 2;

    if (minHeap->heap[parentIndex] > minHeap->heap[index]) {
        swap(&minHeap->heap[parentIndex], &minHeap->heap[index]);
        upheap(minHeap, parentIndex);
    }
}
// remove시에 lastnode와 자리를 바꾸고 제거한 후 그렇게 이동한 lastnode의 위치를 맞추도록 내려오는 작용
void downheap(MinHeap* minHeap, int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int minIndex = index;

    if (leftChildIndex < minHeap->size && minHeap->heap[leftChildIndex] < minHeap->heap[minIndex]) {
        minIndex = leftChildIndex;
    }

    if (rightChildIndex < minHeap->size && minHeap->heap[rightChildIndex] < minHeap->heap[minIndex]) {
        minIndex = rightChildIndex;
    }

    if (minIndex != index) {
        swap(&minHeap->heap[minIndex], &minHeap->heap[index]);
        downheap(minHeap, minIndex);
    }
}
// lastnode에 추가하고 자리가 맞을때까지 upheap하기
void insert(MinHeap* minHeap, int value) {
    // array가 가득 찻을때(insert불가능)
    if (minHeap->size >= MAX_HEAP_SIZE) {
        printf("Heap is full\n");
        return;
    }
    // insert가능하면 upheap반복하기
    minHeap->heap[minHeap->size] = value;
    upheap(minHeap, minHeap->size);
    minHeap->size++;
}
// lastnod와 제거할 노드의 위치를 바꾼후 제거하고
// 이동한 last node의 대소관계가 성립할때까지 downheap을 반복하기
int removeMin(MinHeap* minHeap) {
    // array가 비어있을 경우 remove 불가능
    if (minHeap->size <= 0) {
        printf("Heap is empty.\n");
        return -1;
    }

    int minValue = minHeap->heap[0];
    minHeap->size--;
    minHeap->heap[0] = minHeap->heap[minHeap->size];
    downheap(minHeap, 0);

    return minValue;
}
// 낮은 level부터, 왼쪽자식부터 (array배치 순서가 이러하다.)
void displayHeap(MinHeap* minHeap) {
    printf("Heap: ");
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->heap[i]);
    }
    printf("\n");
}

int main() {
    MinHeap minHeap;
    minHeap.size = 0;
    
    insert(&minHeap, 5);
    printf("insert node_val 5\n");
    insert(&minHeap, 3);
    printf("insert node_val 3\n");
    insert(&minHeap, 8);
    printf("insert node_val 8\n");
    insert(&minHeap, 2);
    printf("insert node_val 2\n");

    displayHeap(&minHeap);  // Output: Heap: 2 3 8 5

    int minValue = removeMin(&minHeap);
    printf("Removed min element: %d\n", minValue);  // Output: Removed min element: 2

    displayHeap(&minHeap);  // Output: Heap: 3 5 8

    return 0;
}


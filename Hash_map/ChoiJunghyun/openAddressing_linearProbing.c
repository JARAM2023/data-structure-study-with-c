#include <stdio.h>
#include <stdlib.h>
// 해시맵이란 해시테이블이라고도 하며 key와 value값을 가지는 값을 index배열에 담는데 담을 index 해쉬함수를 이용해 추출하여 충돌이 없을때는 O(1)의 속도로 삽입&삭제&get을 수행가능하다
// 하지만 더 넓은 범위의 값에서 해시함수를 통해 좁아진 결과 해시값이 같은 같이 나오는 충돌현상이 발생하는데 이를 해결하기 위한 방법으로는
// 같은 index에 LinkedList를 이용하여 여러 Key+value값을 가지는 seperate chaining방식은 충돌시 추가&제거&탐색시간이 O(1)보다 증가하게 된다.
// 비어있는 index까지 다음index로 이동하여 빈 공간을 활용하는 open addressing방식이 있고 이 경우에는 적중율에 따라서 해시값에 따라 달라지는 값을 담을 배열을 2배씩 늘린다.
#define SIZE 10 // 해시맵의 크기

// 해시맵의 노드를 나타내는 구조체
typedef struct Node {
    int key;
    int value;
} Node;

// 해시맵을 나타내는 구조체
typedef struct HashMap {
    Node* table[SIZE];
} HashMap;

// 해시 함수: 키를 해시맵의 인덱스로 변환
int hash(int key) {
    return key % SIZE;
}

// 새로운 노드를 생성하는 함수
Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    return newNode;
}

// 해시맵에 새로운 키-값 쌍을 삽입하는 함수
void insert(HashMap* map, int key, int value) {
    int index = hash(key);

    while (map->table[index] != NULL) {
        // 충돌 발생: 선형 탐색
        index = (index + 1) % SIZE;
    }

    Node* newNode = createNode(key, value);
    map->table[index] = newNode;
}

// 해시맵에서 특정 키에 해당하는 값을 찾는 함수
int get(HashMap* map, int key) {
    int index = hash(key);

    while (map->table[index] != NULL) {
        if (map->table[index]->key == key) {
            return map->table[index]->value;
        }

        // 충돌 발생: 선형 탐색
        index = (index + 1) % SIZE;
    }

    return -1; // 키에 해당하는 값이 없는 경우
}

// 해시맵의 내용을 출력하는 함수
void printHashMap(HashMap* map) {
    for (int i = 0; i < SIZE; i++) {
        if (map->table[i] != NULL) {
            printf("%d: (%d, %d)\n", i, map->table[i]->key, map->table[i]->value);
        } else {
            printf("%d: NULL\n", i);
        }
    }
}

int main() {
    HashMap map;
    for (int i = 0; i < SIZE; i++) {
        map.table[i] = NULL;
    }

    // 해시맵에 키-값 쌍 삽입
    insert(&map, 1, 10);
    insert(&map, 11, 20);
    insert(&map, 21, 30);
    insert(&map, 2, 40);

    // 해시맵의 내용 출력
    printHashMap(&map);

    // 특정 키에 해당하는 값을 찾아 출력
    printf("Value for key 21: %d\n", get

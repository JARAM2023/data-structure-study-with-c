#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 // 해시맵의 크기

// 해시맵의 노드를 나타내는 구조체
typedef struct Node {
    int key;
    int value;
    struct Node* next;
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
    newNode->next = NULL;
    return newNode;
}

// 해시맵에 새로운 키-값 쌍을 삽입하는 함수
void insert(HashMap* map, int key, int value) {
    int index = hash(key);
    Node* newNode = createNode(key, value);

    if (map->table[index] == NULL) {
        // 인덱스에 아무 노드도 없는 경우
        map->table[index] = newNode;
    } else {
        // 인덱스에 이미 노드가 있는 경우
        Node* curr = map->table[index];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

// 해시맵에서 특정 키에 해당하는 값을 찾는 함수
int get(HashMap* map, int key) {
    int index = hash(key);

    if (map->table[index] == NULL) {
        // 키에 해당하는 값이 없는 경우
        return -1;
    } else {
        // 키에 해당하는 값이 있는 경우
        Node* curr = map->table[index];
        while (curr != NULL) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        return -1;
    }
}

// 해시맵의 내용을 출력하는 함수
void printHashMap(HashMap* map) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        Node* curr = map->table[i];
        while (curr != NULL) {
            printf("(%d, %d) ", curr->key, curr->value);
            curr = curr->next;
        }
        printf("\n");
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
    printf("Value for key 21: %d\n", get(&map, 21));
    printf("Value for key 2: %d\n", get(&map, 2));
    printf("Value for key 3: %d\n", get(&map, 3));

    return 0;
}

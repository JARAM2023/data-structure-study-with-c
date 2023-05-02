#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tagNode
{
    char* data;
    struct tagNode* next_node;
} node;

typedef struct tagQueue
{
    node* front;
    node* rear;
    int count;
} Queue;

void createQueue(Queue** queue);
void destroyQueue(Queue* queue);
node* createNode(char* data);
void destroyNode(node* node);
void enqueue(Queue* queue, node* new_node);
node* dequeue(Queue* queue);
int isEmpty(Queue* queue);


void createQueue(Queue** queue)
{
    *queue = (Queue*)malloc(sizeof(queue));
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->count = 0;
}

void destroyQueue(Queue* queue)
{
    while (!isEmpty(queue))
    {
        node* popped = dequeue(queue);
        destroyNode(popped);    
    }

    free(queue);
}

node* createNode(char* new_data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = (char*)malloc(strlen(new_data) + 1);

    strcpy(new_node->data, new_data);  // 데이터 저장 

    new_node->next_node = NULL;     // 다음 노드에 대한 포인터는 NULL로 초기화 

    return new_node;    // 노드의 주소 반환
}

void destroyNode(node* node)
{
    free(node->data);
    free(node);
}

void enqueue(Queue* queue, node* new_node)
{
    if (queue->front == NULL) 
    {        
        queue->front = new_node;
        queue->rear = new_node;
        queue->count++;
    } 
    else
    {
        queue->rear->next_node = new_node;
        queue->rear = new_node;
        queue->count++;
    }
}

node* dequeue(Queue* queue)
{
    // dequeue() 함수가 반환할 최상위 노드 
    node* front = queue->front;

    if (queue->front->next_node == NULL)
    {
        queue->front = NULL;
        queue->rear  = NULL;
    }
    else
    {
        queue->front = queue->front->next_node;
    }

    queue->count--;

    return front;
}

int isEmpty(Queue* queue)
{
    return (queue->front == NULL);
}


int main()
{
    node* popped;
    Queue* queue;

    createQueue(&queue);
    
    enqueue(queue, createNode("Sunbean"));
    enqueue(queue, createNode("Park"));

    printf("queue Size : %d\n", queue->count);

    while (isEmpty(queue) == 0)
    {
        popped = dequeue(queue);
        printf("Dequeue: %s\n", popped->data);
        destroyNode(popped);
    }

    destroyQueue(queue);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode
{
    int data;
} Node;

typedef struct tagDeque
{
    int capacity;
    int front;
    int rear;

    Node* Nodes;
} Deque;

void createQueue(Deque** deque, int capacity);
void destroyQueue(Deque* deque);
void addRear(Deque* deque, int data);
int removeRear(Deque* deque);
int getSize(Deque* deque);
int isEmpty(Deque* deque);
int isFull(Deque* deque);


void  createQueue(Deque** deque, int capacity)
{
    //  큐를 자유 저장소에 생성 
    (*deque) = (Deque*)malloc(sizeof(Deque));

    //  입력된 capacity+1 만큼의 노드를 자유 저장소에 생성 
    (*deque)->Nodes = (Node*)malloc(sizeof(Node)* (capacity+1));

    (*deque)->capacity = capacity;
    (*deque)->front = 0;
    (*deque)->rear = 0;
}

void destroyQueue(Deque* deque)
{
    free(deque->Nodes);
    free(deque);
}

void addRear(Deque* deque, int data)
{
    int Position=0;
  
    if(deque->rear==deque->capacity)
    {
        Position=deque->rear;
        deque->rear=0;
    }
    else
        Position=deque->rear++;
  
    deque->Nodes[Position].data=data;
}

int removeRear(Deque* deque)
{
    int Position = deque->front;

    if (deque->front == deque->capacity)
        deque->front = 0;
    else
        deque->front++;

    return deque->Nodes[Position].data;
}

int getSize(Deque* deque)
{
    if (deque->front <= deque->rear)
        return deque->rear - deque->front;
    else
        return deque->rear + (deque->capacity - deque->front) + 1;
}

int isEmpty(Deque* deque)
{
    return (deque->front == deque->rear);
}

int isFull(Deque* deque)
{
    if (deque->front < deque->rear)
        return (deque->rear - deque->front) == deque->capacity;
    else
        return (deque->rear + 1) == deque->front;
}



int main()
{
    int i;
    Deque* deque;

    createQueue(&deque, 10);
    
    addRear(deque, 1);
    addRear(deque, 2);
    addRear(deque, 3);
    addRear(deque, 4);

    for ( i=0; i<3; i++)
    {
        printf("Dequeue: %d, ", removeRear(deque));
        printf("Front:%d, Rear:%d\n", deque->front, deque->rear);
    }
    
    i = 100;
    while (isFull(deque) == 0)
    {
        addRear(deque, i++);
    }

    printf( "Capacity: %d, Size: %d\n\n", 
        deque->capacity, getSize(deque));

    while (isEmpty(deque) == 0)
    {        
        printf("Dequeue: %d,", removeRear(deque));
        printf("Front:%d, Rear:%d\n", deque->front, deque->rear);
    }

    destroyQueue(deque);

    return 0;
}

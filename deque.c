#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int front;
    int rear;
    int *data;
    int max;
    int cnt;
}queue;

void qExpand(queue *q);
void enqueue_front(queue *q, int data);
int dequeue_front(queue *q);
void enqueue_back(queue *q, int data);
int dequeue_back(queue *q);

void initQueue(queue *q, int size)
{
    q->data = (int *) malloc(size * sizeof(int)); /* allocate memory for queue*/
    if (!q->data)
        return ;
    q->front = size - 1;
    q->rear = size - 1; /* set the front and rear pointers to the last index */
    q->max = size; /*maximum size of queue */
    q->cnt = 0; /*number of elements */
}

int empty(queue *q)
{
    if (q->rear == q->front)
        return (1);
    return (0);
}

int full(queue *q)
{
    if ((q->rear + 1) % q->max == q->front) /*if the next index after the rear index is the front index */
        return (1);
    return (0);
}

int front(queue *q)
{
    int first_data;

    first_data = (q->front + 1) % q->max;
    if (!empty(q)) /* not empty*/
        return (q->data[first_data]);/*return first data*/
    return (-1);
}

int back(queue *q)
{
    if (!empty(q))/* not empty*/
        return (q->data[q->rear]);/*return last data*/
    return (-1);
}

void qExpand(queue *q)
{
    int i;
    int count;
    int *buf;

    buf = (int *) malloc(q->max * sizeof(int)); /*allocate memory*/
    count = q->cnt;
    i = 0;
    while (i < count)
    {
        buf[i] = dequeue_front(q); /*save element to the buffer*/
        i++;
    }
    q->max *= 2;
    q->data = (int *) realloc(q->data, q->max * sizeof(int));/*reallocate memory*/
    if (!q->data)
        return ;
    count = q->cnt;
    i = 0;
    while (i < count)
    {
        enqueue_front(q, buf[i]);
        i++;
    }
    free(buf);
}

void enqueue_front(queue *q, int data)
{
    if (!full(q))
    {
        q->data[q->front] = data; /*add data to the front of the queue*/
        q->front = (q->front - 1 + q->max) % q->max;
        q->cnt++;
    }
    else
    {
        qExpand(q);
        enqueue_front(q, data);
    }
}

int dequeue_front(queue *q)
{
    if (!empty(q))
    {
        q->front = (q->front + 1) % q->max; /*remove the front element*/
        q->cnt--;
        return (q->data[q->front]);
    }
    return (-1);
}

void enqueue_back(queue *q, int data)
{
    if (!full(q))
    {
        q->rear = (q->rear + 1) % q->max; /*add thedata to the back*/
        q->data[q->rear] = data;
        q->cnt++;
    }
    else
    {
        qExpand(q);
        enqueue_back(q, data);
    }
}

int dequeue_back(queue *q)
{
    int value;

    if (!empty(q))
    {
        value = q->rear;
        q->rear = (q->rear - 1 + q->max) % q->max;
        q->cnt--;
        return (q->data[value]); /*remove the rear */
    }
    return (-1);
}

int main(){
  queue q;
  initQueue(&q,10);
  
    enqueue_front(&q, 10);
    enqueue_front(&q, 20);
    enqueue_back(&q, 30);
    enqueue_back(&q, 40);

    printf("%d ", dequeue_front(&q));
    printf("%d ",dequeue_back(&q));
    return 0;
} /* 20 40 */

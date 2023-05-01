#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
  int data;
  struct Node *next;
}Node;

typedef struct Queue
{
  Node *front;
  Node *rear;
  int count;
}Queue;


void initQueue(Queue *queue)
{
  queue -> front = queue -> rear =NULL; /* set NULL to front, rear */
  queue -> count =0; /* count 0 */
}

int empty(Queue *queue)
{
  return queue->count ==0;
}

void enqueue(Queue *queue, int data)
{
  Node *now = (Node *)malloc(sizeof(Node)); /*allocate memory for a new node */
  now -> data = data; /*set data of the new node to the given data*/
  now -> next = NULL; /*set the next pointer NULL */

  if (empty(queue)) /* if empty */
    {
      queue -> front = now; /*set the front pointer to the new node */
    }
  else /* if not empty */
    {
      queue -> rear -> next = now; /*set the next pointer of the rear node to the new node */
    }
  queue -> rear = now; /*set the rear pointer to the new node */
  queue -> count++; /* increase the count */
}

int dequeue(Queue *queue)
{
  int re = 0;
  Node *now;
  if (empty(queue)) /* if empty */
    {
      return re; /*return 0*/
    }
  now = queue -> front; /*set now to the front node */
  re = now -> data; /*store the data of the front node to re */
  queue -> front = now -> next; /*set the front pointer to the next node*/
  free(now);/*free the memory of the front node*/
  queue -> count--;/*decrease the count*/
  return re;/*return the data of the front node*/
}

int main(){
  int i;
  Queue queue;

  initQueue(&queue);
  for (i=1; i<=5; i++)
    {
      enqueue(&queue, i);
    }
  while (!empty(&queue))
    {
      printf("%d ", dequeue(&queue));
    }
  printf("\n");
  return 0;
} /*1 2 3 4 5*/

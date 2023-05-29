#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
  int top;
  int *data;
  int max;
}stack;

void initStack(stack *st, int size)
{
  st->data = (int *) malloc(size*sizeof(int)); /*allocate memory for the stack */
  st -> top -1; /* empty stack*/
  st -> max = size; /*maximum capacity*/
}

int Top(stack *st)
{
  if (st ->top != -1) /* if not empty */
    return (st ->data[st->top]); /*return the top element */
}

int full(stack *st)
{
  if (st -> top == st -> max-1) /* if the top index is at theh maximum capacity */
    return (1);
  return (0);
}

int empty(stack *st)
{
  if (st->top ==-1) /* if the top index is -1 */
    return (1);
  return (0);
}

void push(stack *st, int data)
{
  if (!full(st)) /* not full */
    {
      st->top ++; /* increase the top index */
      st ->data[st->top] = data; /*add the new element to the top */
    }
    else /* full */
      {
	st ->data = (int *) realloc(st->data, st->max * 2 * sizeof(int)); /*allocate more memory */
	push(st, data);
      }
}
  
int pop(stack *st)
{
  int value;

  if (!empty(st)) /* not empty */
    {
      value = st -> data[st->top]; /* store the top element */
      st->top--; /*decrease the top */
      return (value); /* return the popped value */
    }
  return (0);
}

int main(){
  stack st;
  initStack(&st,100);
  push(&st,1);
  push(&st,2);
  push(&st,3);

  printf("%d ",pop(&st));
  printf("%d ",pop(&st));
  printf("%d ",pop(&st));
} /*3 2 1*/

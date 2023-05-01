// 양쪽 끝 삽입.삭제 가능(스택+큐)
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 5
typedef int element;
typedef struct {
	element  data[QUEUE_SIZE];
	int  front, rear;
} DequeType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_deque(DequeType *q)
{
	q->front = q->rear =  0;
}

int is_empty(DequeType *q)
{
	return (  q->front == q->rear );
}

int is_full(DequeType *q)
{
	return (( q->rear  + 1) % QUEUE_SIZE == q->front);
}

void deque_print(DequeType *q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front; // i에 현재 q의 front값을 넣어주고
		do {
			i = (i + 1) % (QUEUE_SIZE); // i의 자리를 1증가
			printf("%d | ", q->data[i]); // 증가한 i 자리에 해당하는 data값을 출력
		} while ( i != q->rear); 
	}
	printf("\n");
}

void add_rear(DequeType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % QUEUE_SIZE; // rear값 1 증가
	q->data[ q->rear ] = item;
}

element delete_rear(DequeType *q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear =  (q->rear - 1 + QUEUE_SIZE) % QUEUE_SIZE; // rear값 1감소
	return q->data[prev];
}

element get_rear(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[ q->rear ];
}

void add_front(DequeType *q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[ q->front ] = val;
	q->front = (q->front - 1 + QUEUE_SIZE) % QUEUE_SIZE; // front값 1감소
} 

element delete_front(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front =  (q->front + 1) % QUEUE_SIZE  ; // front값 1 증가
	return q->data[ q->front ];
}

element get_front(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[ (q->front + 1) % QUEUE_SIZE ];
}

int main(void)
{
	DequeType queue;

	init_deque(&queue);
	
		add_front(&queue, 9);   // 9 |
		deque_print(&queue);

		add_front(&queue, 2);   // 2 | 9 |
		deque_print(&queue);

        add_rear(&queue, 7);    // 2 | 9 | 7 |
		deque_print(&queue);

		delete_rear(&queue);    // 2 | 9 |
		deque_print(&queue);

		add_rear(&queue, 3);    // 2 | 9 | 3 |
		deque_print(&queue);

		delete_front(&queue);   // 9 | 3 |
		deque_print(&queue);
	return 0;
}
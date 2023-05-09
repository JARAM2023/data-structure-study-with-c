#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    char* data;
    struct node* next_node;
} node;

typedef struct stack
{
    node* list;
    node* top;
} Stack;

void createStack(Stack** stack);
void destroyStack(Stack* stack);
node* createNode(char* data);
void destroyNode(node* node);
void push(Stack* stack, node* new_node);
node* pop(Stack* stack);
node* top(Stack* stack);
int isEmpty(Stack* stack);


void createStack(Stack** stack)
{
    // 스택을 자유 저장소에 생성 
    *stack = (Stack*)malloc(sizeof(stack));
    (*stack)->list = NULL;
    (*stack)->top = NULL;
}

void destroyStack(Stack* stack)
{
    while (!isEmpty(stack))
    {
        node* popped = pop(stack);
        destroyNode(popped);    
    }

    free(stack);
}

node* createNode(char* new_data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = (char*)malloc(strlen(new_data) + 1);

    strcpy(new_node->data, new_data);  // 데이터를 저장 

    new_node->next_node = NULL; // 다음 노드에 대한 포인터는 NULL로 초기화 

    return new_node; // 노드의 주소를 반환 
}

void  destroyNode(node* node)
{
    free(node->data);
    free(node);
}

void push(Stack* stack, node* new_node)
{
    if (stack->list == NULL)    
        stack->list = new_node; 
    else    
        stack->top->next_node = new_node;      //스택의 top에 신규 노드를 연결
    
    stack->top = new_node;          // 스택의 top 필드에 새 노드의 주소를 등록 
}

node* pop(Stack* stack)
{
    // pop() 함수가 반환할 최상위 노드 저장 
    node* top_node = stack->top;

    if (stack->list == stack->top)
    {
        stack->list = NULL;
        stack->top = NULL;
    }
    else
    {
        // top 아래에 있던 노드를 새로운 CurrentTop에 저장 
        node* current_top = stack->list;
        while (current_top != NULL && current_top->next_node != stack->top)
        {
            current_top = current_top->next_node;
        }

        // CurrentTop을 Top에 저장
        stack->top = current_top;
        stack->top->next_node = NULL;
    }

    return top_node;
}

node* top(Stack* stack)
{
    return stack->top;
}

int isEmpty(Stack* stack)
{
    return (stack->list == NULL);
}


int main()
{
    int count = 2;
    node* popped;
    Stack* stack;

    createStack(&stack);
    
    push(stack, createNode("Sunbean"));
    push(stack, createNode("Park"));

    printf("Size: %d, Top: %s\n", count, top(stack)->data);

    for (int i=0; i<count; i++)
    {
        if (isEmpty(stack)) break;

        popped = pop(stack);
        printf("Popped: %s, ", popped->data);

        destroyNode(popped);

        if (!isEmpty(stack)) printf("Current Top: %s\n", top(stack)->data);
        else printf("Stack Is Empty.\n");
    }

    destroyStack(stack);

    return 0;
}

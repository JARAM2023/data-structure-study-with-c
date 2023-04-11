
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* next_node;
    int data; 
} Node;


Node* createNode(int newdata);
void  destroyNode(Node* node);
void  addNode(Node** head, Node* newNode);
void  insertAfterNode(Node* current, Node* newNode);
void  insertNewHead(Node** head, Node* newHead);
void  deleteNode(Node** head, Node* remove);
Node* searchNode(Node* head, int location);
int   countNode(Node* head);


//  노드 생성 
Node* createNode(int newdata)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = newdata;  //  데이터를 저장한다. 
    newNode->next_node = NULL; //  다음 노드에 대한 포인터는 NULL로 초기화 한다. 

    return newNode;//  노드의 주소를 반환한다. 
}

//  노드 소멸 
void destroyNode(Node* Node)
{
    free(Node);
}

//  노드 추가 
void addNode(Node** head, Node* newNode)
{
    //  헤드 노드가 NULL이라면 새로운 노드가 Head 
    if ( (*head) == NULL ) 
    {        
        *head = newNode;
    } 
    else
    {
        //  테일을 찾아 newNode를 연결한다. 
        Node* tail = (*head);
        while (tail->next_node != NULL)
        {
            tail = tail->next_node;
        }

        tail->next_node = newNode;
    }
}

//  노드 삽입 
void insertAfterNode(Node* current, Node* newNode)
{
    newNode->next_node = current->next_node;
    current->next_node = newNode;
}

void  insertnewHead(Node** head, Node* newHead)
{
    if (head == NULL)
    {
        (*head) = newHead;    
    }
    else
    {
        newHead->next_node = (*head);
        (*head) = newHead;
    }
}

//  노드 제거 
void deleteNode(Node** head, Node* remove)
{
    if (*head == remove)
    {
        *head = remove->next_node;
    }
    else
    {
        Node* current = *head;
        while (current != NULL && current->next_node != remove)
        {
            current = current->next_node;
        }

        if (current != NULL) {
            current->next_node = remove->next_node;
        }
    }
}

//  노드 탐색 
Node* searchNode(Node* head, int location)
{
    Node* current = head;

    while ( current != NULL && (--location) >= 0)
    {
        current = current->next_node;
    }

    return current;
}

//  노드 개수 세기 
int countNode(Node* head)
{
    int   count = 0;
    Node* current = head;

    while (current != NULL)
    {
        current = current->next_node;
        count++;
    }

    return count;
}


int main()
{
    int   i       = 0;
    int   count   = 0;
    Node* list    = NULL;
    Node* current = NULL;
    Node* newNode = NULL;

    //  노드 5개 추가 
    for (i=0; i<5; i++)
    {
        newNode = createNode(i);
        addNode(&list, newNode);
    }

    newNode = createNode(-1);
    insertNewHead(&list, newNode);

    newNode = createNode(-2);
    insertNewHead(&list, newNode);

    //  리스트 출력 
    count = countNode(list);
    for (i=0; i<count; i++)
    {
        current = searchNode(list, i);
        printf("list[%d] : %d\n", i, current->data);
    }

    //  리스트의 세번째 노드 뒤에 새 노드 삽입 
    printf("\nInserting 3000 After[2]...\n\n");

    current = searchNode(list, 2);
    newNode  = createNode(3000);

    insertAfterNode(current, newNode);

    //  리스트 출력 
    count = countNode(list);
    for (i=0; i<count; i++)
    {
        current = searchNode(list, i);
        printf("list[%d] : %d\n", i, current->data);
    }

    //  모든 노드를 메모리에서 제거     
    printf("\nDestroying list...\n");

    for (i=0; i<count; i++)
    {
        current = searchNode(list, 0);

        if (current != NULL) 
        {
            deleteNode(&list, current);
            destroyNode(current);
        }
    }

    return 0;
}

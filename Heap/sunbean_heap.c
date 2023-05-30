#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct heapNode {
    int data;
} HeapNode;

typedef struct heap {
    HeapNode* Nodes;
    int capacity;
    int used_size;
} Heap;

Heap* create(int size);
void destroy(Heap* h);
void insert(Heap* h, int new_data);
void deleteMin(Heap* h, HeapNode* root);
void swap(Heap* h, int i1, int i2);
void printNode(Heap* h);


Heap* create(int size)
{
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->capacity = size;
    heap->used_size = 0;
    heap->Nodes = (HeapNode*) malloc(sizeof(HeapNode) * heap->capacity);

    return heap;
}

void destroy(Heap* h)
{
    free(h->Nodes);
    free(h);
}

void insert(Heap* h, int new_data)
{
    int current = h->used_size;
    int parent  = (int)((current-1) / 2);

    if (h->used_size == h->capacity) 
    {
        h->capacity *= 2;
        h->Nodes = (HeapNode*) 
        realloc(h->Nodes, sizeof(HeapNode) * h->capacity);
    }
    h->Nodes[current].data = new_data;

    while(current > 0 && h->Nodes[current].data < h->Nodes[parent].data)
    {
        swap(h, current, parent);
        current = parent;
        parent= (int)((current-1) / 2);
    }
    h->used_size++;
}

void swap(Heap* h, int i1, int i2)
{ 
    int CopySize = sizeof(HeapNode);
    HeapNode* Temp = (HeapNode*)malloc(CopySize);
        
    memcpy(Temp,&h->Nodes[i1], CopySize);
    memcpy(&h->Nodes[i1], &h->Nodes[i2], CopySize);
    memcpy(&h->Nodes[i2], Temp, CopySize);

    free(Temp);
}

void deleteMin(Heap* h, HeapNode* root)
{
    int parent = 0;
    int left = 0;    
    int right = 0;    
    
    memcpy(root, &h->Nodes[0], sizeof(HeapNode));
    memset(&h->Nodes[0], 0, sizeof(HeapNode));

    h->used_size--;
    swap(h, 0, h->used_size);

    left = 1;
    right = left + 1;

    while(1)
    {
        int child = 0;

        if (left >= h->used_size)
            break;

        if (right >= h->used_size)
        {
            child = left;
        }
        else {
            if (h->Nodes[left].data > h->Nodes[right].data)
                child = right;
            else
                child = left;                
        }

        if (h->Nodes[child].data < h->Nodes[parent].data)
        {
            swap(h, parent, child);
            parent = child;
        }
        else
            break;

        left = (2 * parent + 1);
        right = left + 1;
    }

    if (h->used_size < (h->capacity / 2)) 
    {
        h->capacity /= 2;
        h->Nodes = (HeapNode*)realloc(h->Nodes, sizeof(HeapNode) * h->capacity);
    }
}

void printNode(Heap* h)
{
    int i = 0;
    for (i=0; i < h->used_size; i++)
    {
        printf("%d ", h->Nodes[i].data);
    }
    printf("\n");
}

int main()
{
    Heap* h = create(3);
    HeapNode min;
    
    insert(h, 5);
    insert(h, 6);
    insert(h, 7);
    printNode(h);
    
    deleteMin(h, &min);
    printNode(h);

    deleteMin(h, &min);
    printNode(h);

    deleteMin(h, &min);
    printNode(h);

    return 0;
}

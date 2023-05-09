#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define M 5
#define MAX_CHILDREN M
#define MAX_KEYS MAX_CHILDREN-1
#define MIN_KEYS (int)(ceil(M/2.0))-1

typedef struct _Node{
    bool leaf;
    int key[MAX_KEYS+1];
    int cnt_key;
    struct _Node* child[MAX_CHILDREN+1];
    int cnt_child;
} Node;

int DeleteValFromNode(int value, Node* node);

Node* root;

int SearchNode(Node* node, int value){
    if (!node){
        printf("Empty tree\n");
        return 0;
    }
    Node* level = node;
    while (true){
        int position;
        for (position=0; position < level->cnt_key; position++){
            if (value == level->key[position]){
                printf("key %d exists!\n",value);
                return 1;
            }
            else if (value < level->key[position]) break;
        }
        if (level->leaf) break;
        level = level->child[position];
    }
    printf("key %d does not exist",value);
    return 0;
}


Node* CreateNode(int value){ 
    Node* new_node;
    new_node = (Node*)malloc(sizeof(Node));
    new_node->leaf = false;
    new_node->key[0] = value;
    new_node->cnt_key = 1;
    new_node->cnt_child = 0;
    return new_node;
}


Node* SplitNode(int pos, Node* node, Node* parent){
    int median;
    median = node->cnt_key / 2;
    Node* right_node;

    right_node = (Node*)malloc(sizeof(Node));
    right_node-> leaf = node->leaf;
    right_node-> cnt_key = 0;
    right_node-> cnt_child = 0;

    int num_iter = node->cnt_key;
    for(int i = median+1; i< num_iter; i++){
        right_node->key[i-(median+1)] = node->key[i];
        right_node ->cnt_key++;
        node->cnt_key--;
    }

    if (!node->leaf){
        num_iter = node->cnt_child;
        for (int i = median+1; i < num_iter; i++ ) {
            right_node->child[i-(median+1)] = node ->child[i];
            right_node-> cnt_child++;
            node->cnt_child--;
        }
    }


    if (node==root) {
        Node* new_parent_node;
        new_parent_node = CreateNode(node->key[median]);
        node->cnt_key--;
        new_parent_node->child[0] = node;
        new_parent_node->child[1] = right_node;

        new_parent_node->cnt_child = 2;
        return new_parent_node; 
    }
    else {
        for (int i= parent->cnt_key; i> pos; i--){
            parent->key[i] = parent->key[i-1];
            parent->child[i+1] = parent->child[i];
        }

        parent->key[pos]= node->key[median];
        parent->cnt_key++;
        node->cnt_key--;
        parent-> child[pos+1] = right_node;
        parent->cnt_child+=1;
    }
    return node;
}


Node* insertNode(int parent_pos, int value, Node* node, Node* parent) {
    int position;
    for (position=0; position < node->cnt_key; position++ ) {
        if (value == node -> key[position]){
            printf("Duplicates are not permitted!\n");
            return node;
        }
        else if (value< node->key[position]){
            break;
        }
    }
    if (!node->leaf) {
        node->child[position] = insertNode(position, value, node->child[position] ,node);
        if (node->cnt_key == MAX_KEYS +1){
            node = SplitNode(parent_pos, node,parent);
        }
    }
    else {
        for (int i = node->cnt_key; i > position; i--) {
            node->key[i] = node->key[i-1];
            node->child[i+1] = node->child[i];
        }

        node->key[position] = value;
        node->cnt_key++;
        if (node->cnt_key == MAX_KEYS+1){
            node = SplitNode(parent_pos, node, parent);
        }
    }   
    return node;
}


void insert(int value){
    if (!root){
        root = CreateNode(value);
        root -> leaf = true;
        return;
    }
    else{
        root = insertNode(0, value, root, root);
    }
}

void mergeNode(Node* parent_node, int node_position, int merge_node_position){
    int merge_idx = parent_node->child[merge_node_position]->cnt_key;
    parent_node->child[merge_node_position]->key[merge_idx]= parent_node->key[merge_node_position];
    parent_node->child[merge_node_position]->cnt_key++;

    for(int i=0; i<parent_node->child[node_position]->cnt_key; i++){
        parent_node->child[merge_node_position]->key[merge_idx+1+i] = parent_node->child[node_position]->key[i];
        parent_node->child[merge_node_position]->cnt_key++;
    }

    int merge_childidx = parent_node->child[merge_node_position]->cnt_child;
    for (int i=0; i<parent_node->child[node_position]->cnt_child; i++){
        parent_node->child[merge_node_position]->child[merge_childidx+i] = parent_node->child[node_position]->child[i];
        parent_node->child[merge_node_position]->cnt_child++;
    }

    free(parent_node->child[node_position]);

    for(int i = merge_node_position; i < (parent_node->cnt_key)-1; i++) {
        parent_node->key[i] = parent_node->key[i+1];
    }
    parent_node->cnt_key--;

    for(int i = merge_node_position+1; i<(parent_node->cnt_child)-1; i++){
        parent_node->child[i] = parent_node->child[i+1];
    }
    parent_node->cnt_child--;
}


void BorrowFromLeft(Node* parent_node, int cur_node_position){
    int tenant_idx = 0;

    for (int i=0; i< parent_node->child[cur_node_position]->cnt_key; i++){ 
        parent_node->child[cur_node_position]->key[i+1] = parent_node->child[cur_node_position]->key[i];
    }
    parent_node->child[cur_node_position]->key[tenant_idx] = parent_node->key[cur_node_position-1];
    parent_node->child[cur_node_position]->cnt_key++;

    int idx_from_sib_topar= (parent_node->child[cur_node_position-1]->cnt_key) -1;
    parent_node->key[cur_node_position-1] = parent_node->child[cur_node_position-1]->key[idx_from_sib_topar];
    parent_node->child[cur_node_position-1]->cnt_key--;

    if (parent_node->child[cur_node_position-1]->cnt_child>0){
        int tenant_childidx = (parent_node->child[cur_node_position-1]->cnt_child)-1;
        for (int i = parent_node->child[cur_node_position]->cnt_child; i > 0; i--){
            parent_node->child[cur_node_position]->child[i] = parent_node->child[cur_node_position]->child[i-1];
        }

        parent_node->child[cur_node_position]->child[0] = parent_node->child[cur_node_position-1]->child[tenant_childidx];
        parent_node->child[cur_node_position]->cnt_child++;

        parent_node->child[cur_node_position-1]->cnt_child--;
    }
}


void BorrowFromRight(Node* par_node, int cur_node_pos){
    int tenant_idx = par_node->child[cur_node_pos]->cnt_key;
    par_node->child[cur_node_pos]->key[tenant_idx] = par_node->key[cur_node_pos];
    par_node->child[cur_node_pos]->cnt_key++;

    int idx_from_sib_topar= 0;
    par_node->key[cur_node_pos] = par_node->child[cur_node_pos+1]->key[idx_from_sib_topar];

    for (int i=0; i< (par_node->child[cur_node_pos+1]->cnt_key)-1; i++){ 
        par_node->child[cur_node_pos+1]->key[i] = par_node->child[cur_node_pos+1]->key[i+1];
    }
    par_node->child[cur_node_pos+1]->cnt_key--;

    int idx_from_sib = 0;

    if (par_node->child[cur_node_pos+1]->cnt_child>0){
        int tenant_childidx = par_node->child[cur_node_pos]->cnt_child;
        par_node->child[cur_node_pos]->child[tenant_childidx] = par_node->child[cur_node_pos+1]->child[idx_from_sib];
        par_node->child[cur_node_pos]->cnt_child++;

        for (int i = 0; i<par_node->child[cur_node_pos+1]->cnt_child-1; i++){
            par_node->child[cur_node_pos+1]->child[i] = par_node->child[cur_node_pos+1]->child[i+1];
        }
        par_node->child[cur_node_pos+1]->cnt_child--;
    }
}

void BalanceNode(Node* node, int child_pos){
    if (child_pos==0){
        if (node->child[child_pos+1]->cnt_key > MIN_KEYS){
            BorrowFromRight(node,child_pos);
        }
        else{
            mergeNode(node,child_pos+1,child_pos);
        }
        return;
    }

    else if (child_pos == (node->cnt_key)){
        if (node->child[child_pos-1]->cnt_key > MIN_KEYS){
            BorrowFromLeft(node,child_pos);
        }
        else{
            mergeNode(node,child_pos,child_pos-1);
        }
        return;
    }
    else{
        if (node->child[child_pos-1]->cnt_key > MIN_KEYS){
            BorrowFromLeft(node,child_pos); 
        }
        else if (node->child[child_pos+1]->cnt_key > MIN_KEYS){
            BorrowFromRight(node,child_pos);
        }
        else{
            mergeNode(node,child_pos,child_pos-1);
        }
        return;
    }
}


int MergeChildNode(Node* par_node, int cur_node_pos){
    int mergeidx = par_node->child[cur_node_pos]->cnt_key;

    int value_par_node = par_node->key[cur_node_pos];
    par_node->child[cur_node_pos]->key[mergeidx] = par_node->key[cur_node_pos]; 
    par_node->child[cur_node_pos]->cnt_key++;

    for (int i=0; i < par_node->child[cur_node_pos+1]->cnt_key; i++){
        par_node->child[cur_node_pos]->key[mergeidx+1+i] = par_node->child[cur_node_pos+1]->key[i];
        par_node->child[cur_node_pos]->cnt_key++;
    }
    for (int i=0; i< par_node->child[cur_node_pos+1]->cnt_child; i++){
        par_node->child[cur_node_pos]->child[mergeidx+1+i] = par_node->child[cur_node_pos+1]->child[i];
        par_node->child[cur_node_pos]->cnt_child++;
    }

    for (int i= cur_node_pos; i<par_node->cnt_key; i++){
        par_node->key[i] = par_node->key[i+1];
        par_node->cnt_key--;
    }
    for (int i = cur_node_pos+1; i < par_node->cnt_child; i++){
        par_node->child[i]= par_node->child[i+1];
        par_node->cnt_child--;
    }
    return value_par_node;

}

int FindPredecessor(Node* cur_node){
    int predecessor;
    if (cur_node->leaf){
        return cur_node->key[cur_node->cnt_key-1];
    }
    return FindPredecessor(cur_node->child[(cur_node->cnt_child)-1]);
}

int OverrideWithPredecessor(Node* par_node, int pos_std_search){
    int predecessor = FindPredecessor(par_node->child[pos_std_search]);
    par_node->key[pos_std_search] = predecessor;
    return predecessor;
}

int FindSuccessor(Node* cur_node){
    int successor;
    if (cur_node->leaf){
        return cur_node->key[0];
    }
    return FindSuccessor(cur_node->child[0]);
}

int OverrideWithSuccessor(Node* par_node, int pos_std_search){
    int successor = FindSuccessor(par_node->child[pos_std_search+1]);
    par_node->key[pos_std_search] = successor;
    return successor;
}

void DeleteInnerNode(Node* cur_node, int cur_node_pos){
    int cessor = 0;
    int deletion_for_merge = 0;

    if (cur_node->child[cur_node_pos]->cnt_key >= cur_node->child[cur_node_pos+1]->cnt_key){ 
        if(cur_node->child[cur_node_pos]->cnt_key > MIN_KEYS){
            cessor = OverrideWithPredecessor(cur_node,cur_node_pos);
            DeleteValFromNode(cessor,cur_node->child[cur_node_pos]);
        }
        else{
            deletion_for_merge = MergeChildNode(cur_node,cur_node_pos);
            DeleteValFromNode(deletion_for_merge, cur_node->child[cur_node_pos]);
        }
    }
    else {
        if (cur_node->child[cur_node_pos+1]->cnt_key > MIN_KEYS){
            cessor = OverrideWithSuccessor(cur_node,cur_node_pos);
            DeleteValFromNode(cessor,cur_node->child[cur_node_pos+1]);
        }
        else{
            deletion_for_merge = MergeChildNode(cur_node,cur_node_pos);
            DeleteValFromNode(deletion_for_merge, cur_node->child[cur_node_pos]);
        }

    }

}

int DeleteValFromNode(int value, Node* node){ 
    int pos;
    int flag = false;
    for (pos=0; pos < node->cnt_key; pos++){
        if (value == node->key[pos]){
            flag = true;
            break;
        }
        else if (value< node->key[pos]){
            break;
        }
    }
    if (flag){
        if (node->leaf){
            for (int i = pos; i<node->cnt_key; i++){
                node->key[i] = node->key[i+1];
            }
            node->cnt_key--;
        }
        else {
                DeleteInnerNode(node,pos);
        }
        return flag;
    }
    else {
        if (node->leaf) {
            return flag;
        }
        else{
            flag = DeleteValFromNode(value, node->child[pos]);
        }
    }
    if (node->child[pos]->cnt_key < MIN_KEYS){
        BalanceNode(node,pos);
    }

    return flag;    
}


void delete(Node* node, int value){
    if (!node){
        printf("Empty tree\n");
        return;
    }
    int flag = DeleteValFromNode(value,node);
    if (!flag){
        printf("%d does not exist in this tree. \n", value);
        return;
    }
    if (node->cnt_key == 0){
        node = node->child[0];
    }
    root = node;

}

void printTree(Node* node, int level) {
	if (!node) {
		printf("Empty tree\n");
		return;
	}
	printf("Level %d :", level);
	for (int i = 0; i < level - 1; i++) {
		printf("    ");
	}
	for (int i = 0; i < node->cnt_key; i++) {
		printf("%d ", node->key[i]);
	}
	printf("\n");
	level++;
	for (int i = 0; i < node->cnt_child; i++) {
		printTree(node->child[i], level);
	}
}

int main(void) {
	insert(10);
	insert(20);
	insert(30);
	insert(40);
	insert(50);
	insert(60);
	insert(70);

	printTree(root, 1);
	printf("****************************************************\n");
	delete(root, 103);
	delete(root, 70);
	delete(root, 130);

	printTree(root, 1);

    SearchNode(root,30);

	return 0;
}

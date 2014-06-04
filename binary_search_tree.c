#include<stdio.h>
#include "binary_search_tree.h"

const int NODE_POOL_SIZE = 128;

TreeNodePool* new_node_pool();

TreeNode* new_node(TreeNodePool *node_pool, int val){
	//printf("new_node\n");
	TreeNode *newNode;
	for(int i=0;i<node_pool->pool_size;i++){
		if(*(node_pool->available+i) == 1){
			*(node_pool->available+i) = 0;
			newNode = node_pool->nodes+i;
			newNode->val = val;
			newNode->left = NULL;
			newNode->right = NULL;
			return newNode;
		}
	}
	return NULL;
}

SearchTree* new_search_tree(){
	//printf("new_search_tree\n");
	SearchTree *tree = malloc(sizeof(SearchTree));
	tree->head = NULL;
	tree->max = 0;
	tree->min = 0;
	tree->depth = 0;
	tree->node_count = 0;
	tree->node_pool = new_node_pool();
	return tree;
}

TreeNodePool* new_node_pool(){
	//printf("new_node_pool\n");
	TreeNodePool *pool = malloc(sizeof(TreeNodePool));
	pool->pool_size = NODE_POOL_SIZE;
	pool->nodes =  (TreeNode *)malloc(sizeof(TreeNode)*NODE_POOL_SIZE);
	pool->available = (int *)malloc(sizeof(int)*NODE_POOL_SIZE);
	for(int i=0;i<NODE_POOL_SIZE;i++){
		*(pool->available+i) = 1;
	}
	return pool;
}

TreeNode* insert_node(SearchTree *tree, TreeNode *head, int value){
	if (head == NULL){
		//printf("insert node head:NULL value:%d\n",value);
		head = new_node(tree->node_pool, value);
	}else{
		//printf("insert node head:%d value:%d\n", head->val,value);
		if (head->val > value){
			head->left = insert_node(tree, head->left, value); 
		}
		else if (head->val < value){
			head->right = insert_node(tree, head->right, value);
		}
	}
	return head;
}

int insert(SearchTree *tree, int value){
	//printf("insert %d\n", value);
	int succ = insert_node(tree, tree->head,value);
	if (succ){
		if (value > tree->max){
			tree->max = value;
		}
		if (value < tree->min){
			tree->min = value;
		}
		tree->node_count++;
		tree->depth = max_depth(tree->head);
	}
	return succ;
}

int delete(SearchTree *tree, int value){
	//TODO
	return 1;
}

SearchTree* build_tree(int values[], int n){
	int cur = 0;
	SearchTree *tree = new_search_tree();
	TreeNode *head = new_node(tree->node_pool, values[0]);
	tree->head = head;
	for (int i = 1; i < n; i++){
		insert(tree, values[i]);
	}
	return tree;
}

TreeNode* search_node(SearchTree *tree, int value){
	TreeNode *cur = tree->head;
	while (cur!=NULL)
	{
		if (cur->val == value){
			return cur;
		}
		if (cur->val > value){
			cur = cur->left;
		}
		else{
			cur = cur->right;
		}
	}
	return NULL;
}

int max_depth(TreeNode *root){
	if (root == NULL){
		return 0;
	}
	int maxLeft = max_depth(root->left);
	int maxRight = max_depth(root->right);
	int max = (maxLeft > maxRight) ? maxLeft : maxRight;
	return max + 1;
}

int is_same_tree(TreeNode *p, TreeNode *q){
	if (p == NULL && q == NULL){
		return 1;
	}
	else if (p != NULL && q != NULL){
		int leftEq = is_same_tree(p->left, q->left);
		int rightEq = is_same_tree(p->right, q->right);
		int eq = leftEq && rightEq && (p->val == q->val);
		return eq;
	}
	else{
		return 0;
	}
}

void dump_tree(SearchTree *tree){
	printf("BST values(");
	TreeNode *head = tree->head;
	print_node(head);
	printf(") min=%d max=%d depth=%d\n",tree->min,tree->max,tree->depth);
}

void print_node(TreeNode *node){
	if (node == NULL){
		return;
	}
	print_node(node->left);
	printf("%d ",node->val);
	print_node(node->right);
}
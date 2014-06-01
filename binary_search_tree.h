#include<stdio.h>

typedef struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

typedef struct SearchTree{
	struct TreeNode *head;
	int depth;
	int node_count;
	int max;
	int min;
}SearchTree;

int max_depth(TreeNode *root);

int is_same_tree(TreeNode *p, TreeNode *q);

SearchTree* build_tree(int values[], int n);

void print_node(TreeNode *node);

void dump_tree(SearchTree *tree);

TreeNode* search_node(SearchTree *tree, int value);

int insert(SearchTree *tree, int value);

int delete(SearchTree *tree, int value);

#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}
#include <stdlib.h>
#include <stdbool.h>

#ifndef __SORTS_H__
#define __SORTS_H__

typedef struct _Node {
	int    value;
	struct _Node* next;
} Node;

typedef struct _PriorityQueue {
	int    size;
	struct _Node* head;
} PriorityQueue;

typedef struct _BST {
	int    size;
	struct _BSTNode* root;
} BST;

typedef struct _BSTNode {
	int    value;
	struct _BSTNode* left;
	struct _BSTNode* right;
} BSTNode;

// Queue Sort functions
void pq_sort_array(int* array, size_t size);
PriorityQueue create_pq(const int* array, int size);
void destroy_pq(PriorityQueue* a_pq);

// Tree Sort Functions
void tree_sort_array(int* array, size_t size);
BST create_bst(const int* array, int size);
void destroy_bst(BST* a_bst);

#endif /* end of include guard: __SORTS_H__ */

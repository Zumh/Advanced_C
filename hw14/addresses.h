#include <stdlib.h>
#include <stdbool.h>

#ifndef __ADDRESSES_H__
#define __ADDRESSES_H__

typedef struct _Node {
	void*  a_value;
	struct _Node* next;
} Node;

typedef struct _BSTNode {
	void*  a_value;
	struct _BSTNode* left;
	struct _BSTNode* right;
} BSTNode;

// Linked List Functions
void stack_push(Node** a_top, void* a_value);
Node* stack_pop(Node** stack);
void pq_enqueue(Node** a_head, void* a_value, int(*cmp_fn)(const void*, const void*));
Node* pq_dequeue(Node** a_head);
void print_list(Node* head, void(*print_fn)(const void*));
void destroy_list(Node** a_head, void(*destroy_fn)(void*));

// Binary Tree Functions
void bst_insert(BSTNode** a_root, void* a_value, int(*cmp_fn)(const void*, const void*));
void print_tree(BSTNode* root, void(*print_fn)(const void*));
void destroy_tree(BSTNode** a_root, void(*destroy_fn)(void*));

#endif /* end of include guard: __ADDRESSES_H__ */

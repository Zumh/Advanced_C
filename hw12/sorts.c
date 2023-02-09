#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

// Queue Sort Code

void _enqueue(int value, Node** a_head) {	// helper (SUGGESTED)
	Node* new_node = malloc(sizeof(*new_node));			// Allocate memory for one node
	*new_node = (Node) { .value = value, .next = NULL}; // Initialize it
	if (*a_head == NULL || value <= (*a_head)->value) { // Node goes to start
		new_node->next = *a_head;						// Ensure original list is kept
		*a_head = new_node;								// Update the head
	} else {
		Node* prev = *a_head;							// Start at the beginning
		while (prev->next != NULL && value > prev->next->value) { 	// Seach until end
			prev = prev->next;						// or a node with a larger value
		}
		new_node->next = prev->next; 	// preserve the old nodes
		prev->next = new_node;			// add node into list
	}
}

PriorityQueue create_pq(const int* array, int size) {
	Node* head = NULL;				// Start with an empty list
	for (int idx = 0; idx < size; idx++) {	// For each item in the array
		_enqueue(array[idx], &head);	   	// Insert an item
	}
	return (PriorityQueue) { .head = head, .size = size }; // return the object
}

void destroy_pq(PriorityQueue* a_pq) {
	while(a_pq->head != NULL) {				// If the queue is not empty
		Node* old_head = a_pq->head;		// Don't lose track of the node
		a_pq->head = old_head->next;		// Update the head
		free(old_head);						// Free the old head
	}
	a_pq->size = 0;							// Reset the size
}

void pq_sort_array(int *array, size_t size) {
	PriorityQueue pq = create_pq(array, size);
	int i = 0;
	for (Node* new = pq.head; new != NULL; new = new->next) { 	// For each node
		array[i] = new->value;									// Store value
		i++;							// Update index
	}
	destroy_pq(&pq);					// No Memory Leaks!
}

// BST Code

void _insert(int value, BSTNode** a_root) {		// helper (SUGGESTED)
	if(*a_root == NULL) {
		*a_root = malloc(sizeof(**a_root));		// Allocate memory for one node
		**a_root = (BSTNode) { .value = value, .left = NULL, .right = NULL }; // Set it
	}
	else if(value < (*a_root)->value) {		// If value is less than the value at root
		_insert(value, &((*a_root)->left)); 	// Insert into the left subtree
	}
	else {									// Otherwise...
		_insert(value, &((*a_root)->right));	// Insert into right subtree
	}
}

void _destroy(BSTNode** a_root) {				// helper (SUGGESTED)
	if(*a_root != NULL) {		// If tree is not empty...
		_destroy(&((*a_root) -> left));		// Destroy the left subtree
		_destroy(&((*a_root) -> right)); 	// Destroy the right subtree
		free(*a_root);						// Free (destroy) the root.
	}
	*a_root = NULL; // Set root to null in the caller's stack frame
}

void _fill_array_from_bst(int** a_const_value, BSTNode* node) {	// helper (SUGGESTED)
	if(node != NULL) {								// If the BST is not empty...
		_fill_array_from_bst(a_const_value, node->left);// Traverse left subtree
		**a_const_value = node->value;				 	// Visit root
		*a_const_value += 1;							// Increment index by one
		_fill_array_from_bst(a_const_value, node->right); // Traverse right subtree
	}
}

BST create_bst(const int* array, int size) {
	BST bst = { .root = NULL, .size = size };	// Create a BST object
	for(int idx = 0; idx < size; idx++) {		// For each item in array
		_insert(array[idx], &bst.root); 
	}
	return bst;									// Return the BST object;
}

void destroy_bst(BST* a_bst) {
	_destroy(&(a_bst -> root));
	a_bst->size = 0;							// Update the size
}

void tree_sort_array(int* array, size_t size) {
	BST bst = create_bst(array, size);			// Create a BST
	_fill_array_from_bst(&array, bst.root);		// Fill array 
	destroy_bst(&bst);							// No memory leaks!
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

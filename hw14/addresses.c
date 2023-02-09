#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "addresses.h"

void print_list(Node* head, void(*print_fn)(const void*)) {
	for(Node* node = head; node != NULL; node = node->next) {	// Go through list
		print_fn(node->a_value);								// Print out the value
	}
}

void stack_push(Node** a_top, void* a_value) {
	Node* new_node = malloc(sizeof(*new_node));	// Allocate new node
	*new_node = (Node) { .a_value = a_value, .next = NULL };	// Initialize it

	if(*a_top == NULL) {	// Linked list is empty
		*a_top = new_node; 	// Set the new node 
	}
	else {							// List is not empty
		new_node->next = *a_top;	
		*a_top = new_node;
	}
}

Node* stack_pop(Node** stack) {
	if((*stack) == NULL) {		// Check if it's empty
		return NULL;			// Do nothing
	}
	Node* detatch = *stack;		
	if((*stack)->next == NULL) {	// Is it last node?
		*stack = NULL;				// Set to NULL
	}
	else {							// Not last node
		*stack = (*stack)->next;	// Set address of next node
	}
	detatch->next = NULL;	
	return detatch;
}

void pq_enqueue(Node** a_head, void* a_value, int(*cmp_fn)(const void*, const void*)) {
	Node* new_node = malloc(sizeof(*new_node));					// Allocate new node
	*new_node = (Node) { .a_value = a_value, .next = NULL };	// Initialize it

	if(*a_head == NULL) {
		new_node->next = *a_head;				// Node goes to start
		*a_head = new_node;						// Update head
	} 
	else {
		Node* pos = *a_head;					// Start from beginning
		const void* insert = a_value;			// Set values to compare
		void* num_list = pos->a_value;
		const void* num = num_list;
		int value = cmp_fn(insert, num);
		Node* prev = *a_head;					// Placeholder
		if(value > 0) {
			while(value > 0 && pos->next != NULL) { 	// Go through list
				pos = pos->next;						// Update
				num_list = pos->a_value;				// Set new values
				num = num_list;
				value = cmp_fn(insert, num);			// Compare
				if(value > 0) {				// Check if greater than next
					prev = prev->next;			
				}
			}
			new_node->next = prev->next;		// Add the node to where it belongs
			prev->next = new_node;
		}
		else {
			new_node->next = *a_head;
			*a_head = new_node;
		}
	}
}

Node* pq_dequeue(Node** a_head) {
	if((*a_head) == NULL) {		// Check if it's empty
		return NULL;			// Do nothing
	}
	Node* detatch = *a_head;		
	if((*a_head)->next == NULL) {	// Is it last node?
		*a_head = NULL;				// Set to NULL
	}
	else {							// Not last node
		*a_head = (*a_head)->next;	// Set address of next node
	}
	detatch->next = NULL;	
	return detatch;
}

void destroy_list(Node** a_head, void(*destroy_fn)(void*)) {
	while(*a_head != NULL) {
		destroy_fn((*a_head)->a_value);		// Call destroy function
		Node* old_head = *a_head;			// Don't lose node
		*a_head = (*a_head)->next;			// Update the node
		free(old_head);						// Free the old node
	}
}

void bst_insert(BSTNode** a_root, void* a_value, int(*cmp_fn)(const void*,
			const void*)) {

	if(*a_root == NULL) {
		*a_root = malloc(sizeof(**a_root)); 		// Allocate memory
		**a_root = (BSTNode) { .a_value = a_value, .left = NULL, .right = NULL }; // Set it
	}
	else {
		BSTNode* pos = *a_root;					// Start from beginning
		const void* insert = a_value;			// Set values to compare
		void* num_list = pos->a_value;
		const void* num = num_list;
		int value = cmp_fn(insert, num);

		if(value < 0) {			// Value is less than the value at root
			bst_insert(&((*a_root)->left), a_value, cmp_fn);	// Go to the left
		}
		else {
			bst_insert(&((*a_root)->right), a_value, cmp_fn);	// Go to the right
		}
	}
}

void destroy_tree(BSTNode** a_root, void(*destroy_fn)(void*)) {
	if(*a_root != NULL) {									// If list is not empty
		if((*a_root)->left != NULL) {						// If left is not empty
			destroy_tree(&((*a_root)->left), destroy_fn); 	// Destroy left
		}
		if((*a_root)->right != NULL) {						// If right is not empty
			destroy_tree(&((*a_root)->right), destroy_fn);	// Destroy right
		}
		destroy_fn((*a_root)->a_value);					// Destroy value as needed
		free(*a_root);									// Free root
	}
}

void print_tree(BSTNode* root, void(*print_fn)(const void*)) {
	if(root != NULL) {
		if(root->left != NULL) {
			print_tree(root->left, print_fn);
		}
		const void* value = root->a_value;
		print_fn(value);
		if(root->right != NULL) {
			print_tree(root->right, print_fn);
		}
	}
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

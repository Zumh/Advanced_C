#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

void _print_array(int* array, size_t size, const char* title) {
	printf("%s\n", title);
	for(int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n\n");
}

int main(int argc, char* argv[]) {

	// Demonstrate create_queue(…)
	PriorityQueue pq = create_pq((int[7]) { 4, 2 }, 2);
	assert(pq.head             != NULL && pq.head->value == 2);
	assert(pq.head->next       != NULL && pq.head->next->value == 4);
	assert(pq.head->next->next == NULL);
	// etc.
	destroy_pq(&pq);

	// Demonstrate queue_sort_array(…)
	int array1[] = { 5, 4, 2, 1, 7, 6, 3 };
	size_t size1 = sizeof(array1) / sizeof(*array1);  // # of elements
	_print_array(array1, size1, "Before queue_sort_array(array1)");
	pq_sort_array(array1, size1);
	_print_array(array1, size1, "After  queue_sort_array(array1)");

	// Demonstrate create_bst(…)
	BST bst = create_bst((int[7]) { 4, 2, 6, 1, 3, 5, 7 }, 7);
	assert(bst.root        != NULL && bst.root->value        == 4);
	assert(bst.root->left  != NULL && bst.root->left->value  == 2);
	assert(bst.root->right != NULL && bst.root->right->value == 6);
	destroy_bst(&bst);

	// Demonstrate tree_sort_array(…)
	int array2[] = { 5, 4, 2, 1, 7, 6, 3 };
	size_t size2 = sizeof(array2) / sizeof(*array2);  // # of elements
	_print_array(array2, size2, "Before tree_sort_array(array2)");
	tree_sort_array(array2, size2);
	_print_array(array2, size2, "After  tree_sort_array(array2)");

	return EXIT_SUCCESS;
}
#define DEMO_SORTS_VERSION_3
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

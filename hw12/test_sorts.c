#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "sorts.h"

void _print_sorted_array(int* array, size_t size) {
	for(int idx_in_arr = 0; idx_in_arr < size; idx_in_arr++) {	// Go through array
		printf("%d ", array[idx_in_arr]);	// Print all elements
	}
	printf("}\n"); // Print closing brackets
}

static int _test_create_pq_empty() {
	mu_start();
	//----------------------------
	const int input[] = {0};
	int size = 0;
	PriorityQueue pq = create_pq(input, size);
	mu_check(pq.head == NULL);
	mu_check(pq.size == 0);
	//----------------------------
	mu_end();
}

static int _test_create_pq_not_empty() {
	mu_start();
	//----------------------------
	const int input[] = {1};
	int size = 1;
	PriorityQueue pq = create_pq(input, size);
	mu_check(pq.head != NULL);
	mu_check(pq.head->next == NULL);
	mu_check(pq.head->value == 1);
	destroy_pq(&pq);

	const int input_two[2] = {1, 2};
	size = 2;
	pq = create_pq(input_two, size);
	mu_check(pq.head != NULL);
	mu_check(pq.head->value == 1);
	mu_check(pq.head->next != NULL);
	mu_check(pq.head->next->value == 2);
	mu_check(pq.head->next->next == NULL);
	destroy_pq(&pq);

	const int input_thr[2] = {3, 1};
	size = 2;
	pq = create_pq(input_thr, size);
	mu_check(pq.head != NULL);
	mu_check(pq.head->value == 1);
	mu_check(pq.head->next != NULL);
	mu_check(pq.head->next->value == 3);
	mu_check(pq.head->next->next == NULL);
	destroy_pq(&pq);

	const int input_four[3] = {5, 1, 2};
	size = 3;
	pq = create_pq(input_four, size);
	mu_check(pq.head != NULL);
	mu_check(pq.head->value == 1);
	mu_check(pq.head->next != NULL);
	mu_check(pq.head->next->value == 2);
	mu_check(pq.head->next->next != NULL);
	mu_check(pq.head->next->next->value == 5);
	mu_check(pq.head->next->next->next == NULL);
	destroy_pq(&pq);

	const int input_five[3] = {6, 7, 2};
	size = 3;
	pq = create_pq(input_five, size);
	mu_check(pq.head != NULL);
	mu_check(pq.head->value == 2);
	mu_check(pq.head->next != NULL);
	mu_check(pq.head->next->value == 6);
	mu_check(pq.head->next->next != NULL);
	mu_check(pq.head->next->next->value == 7);
	mu_check(pq.head->next->next->next == NULL);
	destroy_pq(&pq);

	const int input_six[4] = {4, 3, 7, 9};
	size = 4;
	pq = create_pq(input_six, size);
	mu_check(pq.head != NULL);
	mu_check(pq.head->value == 3);
	mu_check(pq.head->next != NULL);
	mu_check(pq.head->next->value == 4);
	mu_check(pq.head->next->next != NULL);
	mu_check(pq.head->next->next->value == 7);
	mu_check(pq.head->next->next->next != NULL);
	mu_check(pq.head->next->next->next->value == 9);
	destroy_pq(&pq);
	//----------------------------
	mu_end();
}

static void _test_pq_sort_array() {

	printf("\nTest PQ Sort Array\n\n");

	int array[] = { 9, 8, 2, 1, 3, 5 };
	size_t size = 6;
	printf("Expected - { 1 2 3 5 8 9 } \n");	
	pq_sort_array(array, size);
	printf("Actual   - { ");
	_print_sorted_array(array, size);

	printf("\n");

	int array_two[] = { 10, 8, 2000, 21, 9, 1990 };
	size = 6;
	printf("Expected - { 8 9 10 21 1990 2000 } \n");
	pq_sort_array(array_two, size);
	printf("Actual   - { ");
	_print_sorted_array(array_two, size);

	printf("\n");
}

static int _test_create_bst_empty() {
	mu_start();
	//----------------------------
	const int input[] = {0};
	int size = 0;
	BST bst = create_bst(input, size);
	mu_check(bst.root == NULL);
	mu_check(bst.size == 0);
	//----------------------------
	mu_end();
}

static int _test_create_bst_not_empty() {
	mu_start();
	//----------------------------
	const int input[2] = {2, 4};
	int size = 2;
	BST bst = create_bst(input, size);
	mu_check(bst.root != NULL);
	mu_check(bst.size == 2);
	mu_check(bst.root->value == 2);
	mu_check(bst.root->left == NULL);
	mu_check(bst.root->right->value == 4);
	mu_check(bst.root->right->right == NULL);
	destroy_bst(&bst);

	const int input_two[3] = {6, 8, 3};
	size = 3;
	bst = create_bst(input_two, size);
	mu_check(bst.root != NULL);
	mu_check(bst.size == 3);
	mu_check(bst.root->value == 6);
	mu_check(bst.root->left != NULL);
	mu_check(bst.root->left->value == 3);
	mu_check(bst.root->right != NULL);
	mu_check(bst.root->right->value == 8);
	mu_check(bst.root->right->right == NULL);
	mu_check(bst.root->right->left == NULL);
	mu_check(bst.root->left->right == NULL);
	mu_check(bst.root->left->left == NULL);
	destroy_bst(&bst);

	const int input_three[4] = {9, 1, 97, 12};
	size = 4;
	bst = create_bst(input_three, size);
	mu_check(bst.root != NULL);
	mu_check(bst.size == 4);
	mu_check(bst.root->value == 9);
	mu_check(bst.root->left != NULL);
	mu_check(bst.root->left->value == 1);
	mu_check(bst.root->right->value == 97);
	mu_check(bst.root->right->left->value == 12);
	mu_check(bst.root->right->right == NULL);
	mu_check(bst.root->left->left == NULL);
	mu_check(bst.root->left->right == NULL);
	destroy_bst(&bst);
	//----------------------------
	mu_end();
}

static void _test_tree_sort_array() {

	printf("\nTest Tree Sort Array\n\n");

	int array[] = { 9, 8, 2, 1, 3, 5 };
	size_t size = 6;
	printf("Expected - { 1 2 3 5 8 9 } \n");	
	tree_sort_array(array, size);
	printf("Actual   - { ");
	_print_sorted_array(array, size);

	printf("\n");

	int array_two[] = {88, 23, 442, 5231, 34};
	size = 5;
	printf("Expected - { 23 34 88 442 5231 } \n");
	tree_sort_array(array_two, size);
	printf("Actual   - { ");
	_print_sorted_array(array_two, size);
}

int main(int argc, char* argv[]) {
	
	mu_run(_test_create_pq_empty);
	mu_run(_test_create_pq_not_empty);
	_test_pq_sort_array();
	mu_run(_test_create_bst_empty);
	mu_run(_test_create_bst_not_empty);
	_test_tree_sort_array();

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

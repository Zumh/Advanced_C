#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "miniunit.h"
#include "addresses.h"

static void _print_integer(const void* a_value) {
	const int* number = a_value;
	int value = *number;
	printf("%d", value);
	fputc('\n', stdout);
}

static void _print_string(const void* a_string) {
	const char* str = a_string;
	printf("%s", str);
	fputc('\n', stdout);
}

static int _compare_strings(const void* first, const void* second) {
	int len_first  = strlen(first);
	int len_second = strlen(second);
	if(len_first < len_second) {
		return -1;
	}
	else if(len_first > len_second) {
		return 1;
	}
	else {
		return 0;
	}
}

static char* _copy_str(const char* a_string) {
	int length = strlen(a_string);
	length += 1;
	char* string = malloc((length) * sizeof(*string));
	strcpy(string, a_string);
	return string;
} 

static int _compare_integers(const void* first, const void* second) {
	const int* first_num  = first;
	const int* second_num = second;
	int 	   first_int  = *first_num;
	int		   second_int = *second_num;

	if(first_int < second_int) {
		return -1;
	}
	else if(first_int > second_int) {
		return 1;
	}
	else {
		return 0;
	}
}

static void _destroy_int_list(void* a_value) {
	// No need to destroy an int so do nothing
}

static void _destroy_str_list(void* a_string) {
	free(a_string);
}

static int _test_stack_push_pop() {
	mu_start();
	//-------------------------
	int num = 10;
	void* value = &num;
	Node* node = malloc(sizeof(*node));
	*node = (Node) { .a_value = value, .next = NULL};
	int num_two= 2;
	value = &num_two;
	stack_push(&node, value);
	mu_check(node != NULL);
	const int* val = node->a_value;
	int cur_val = *val;
	mu_check(cur_val == 2);
	mu_check(node->next != NULL);
	val = node->next->a_value;
	cur_val = *val;
	mu_check(cur_val == 10);
	mu_check(node->next->next == NULL);
	int num_three = 5;
	value = &num_three;
	stack_push(&node, value);
	val = node->a_value;
	cur_val = *val;
	mu_check(cur_val == 5);
	val = node->next->a_value;
	cur_val = *val;
	mu_check(cur_val == 2);
	val = node->next->next->a_value;
	cur_val = *val;
	mu_check(cur_val == 10);
	mu_check(node->next->next->next == NULL);
	printf("Testing Stack Pop/Push\n");
	void(*print_fn)(const void*) = _print_integer;
	print_list(node, print_fn);
	fputc('\n', stdout);

	Node* old = stack_pop(&node);
	val = node->a_value;
	cur_val = *val;
	mu_check(cur_val == 2);
	mu_check(node->next != NULL);
	mu_check(node->next->next == NULL);
	val = old->a_value;
	cur_val = *val;
	mu_check(cur_val == 5);
	mu_check(old->next == NULL);
	free(old);
	val = node->next->a_value;
	cur_val = *val;
	mu_check(cur_val == 10);
	old = stack_pop(&node);
	val = node->a_value;
	cur_val = *val;
	mu_check(cur_val == 10);
	mu_check(node->next == NULL);
	val = old->a_value;
	cur_val = *val;
	mu_check(cur_val == 2);
	mu_check(old->next == NULL);
	void(*destroy_fn)(void*) = _destroy_int_list;
	destroy_list(&old, destroy_fn);
	destroy_list(&node, destroy_fn);

	node = NULL;
	stack_push(&node, value);
	mu_check(node->next == NULL);
	val = node->a_value;
	cur_val = *val;
	mu_check(cur_val == 5);
	int num_four = 3;
	value = &num_four;
	stack_push(&node, value);
	val = node->next->a_value;
	cur_val = *val;
	mu_check(cur_val == 5);
	val = node->a_value;
	cur_val = *val;
	mu_check(cur_val == 3);
	
	Node* old_node = stack_pop(&node);
	val = old_node->a_value;
	cur_val = *val;
	mu_check(cur_val == 3);
	mu_check(old_node->next == NULL);
	free(old_node);
	val = node->a_value;
	cur_val = *val;
	mu_check(cur_val == 5);
	mu_check(node->next == NULL);

	old_node = stack_pop(&node);
	val = old_node->a_value;
	cur_val = *val;
	mu_check(cur_val == 5);
	mu_check(old_node->next == NULL);
	mu_check(node == NULL);
	free(node);
	free(old_node);

	node = NULL;
	old_node = stack_pop(&node);
	mu_check(old_node == NULL);
	mu_check(node == NULL);
	//-------------------------
	mu_end();
}

static void _test_pq_enqueue_dequeue() {
	//-------------------------
	int(*cmp_fn)(const void*, const void*) = _compare_integers;
	void(*print_fn)(const void*) = _print_integer;

	Node* node = NULL;
	int num = 10;
	void* value = &num;
	pq_enqueue(&node, value, cmp_fn);
	int num_two = 8;
	value = &num_two;
	pq_enqueue(&node, value, cmp_fn);
	int num_three = 6;
	value = &num_three;
	pq_enqueue(&node, value, cmp_fn);
	int num_four = 12;
	value = &num_four;
	pq_enqueue(&node, value, cmp_fn);
	int num_five = 9;
	value = &num_five;
	pq_enqueue(&node, value, cmp_fn);

	printf("Testing Function pq_enqueue\n");
	print_list(node, print_fn);
	fputc('\n', stdout);

	Node* old = pq_dequeue(&node);
	printf("After First Dequeue\n");
	print_list(node, print_fn);
	fputc('\n', stdout);
	free(old);

	old = pq_dequeue(&node);
	printf("After Second Dequeue\n");
	print_list(node, print_fn);
	fputc('\n', stdout);
	free(old);
	// Third
	old = pq_dequeue(&node);
	free(old);
	// Fourth
	old = pq_dequeue(&node);
	free(old);
	// Fifth
	old = pq_dequeue(&node);
	free(old);
	// Sixth 
	old = pq_dequeue(&node);
	//-------------------------
}

static void _test_string_enqueue_dequeue() {
	//-------------------------
	int(*cmp_fn)(const void*, const void*) = _compare_strings;
	void(*print_fn)(const void*) = _print_string;
 	Node* node = NULL;
	pq_enqueue(&node, _copy_str("Hello"), cmp_fn);
	pq_enqueue(&node, _copy_str("One"), cmp_fn);
	pq_enqueue(&node, _copy_str("Longest"), cmp_fn);
	pq_enqueue(&node, _copy_str("Four"), cmp_fn);
	pq_enqueue(&node, _copy_str("1"), cmp_fn);

	printf("Testing String Linked List\n");
	print_list(node, print_fn);
	fputc('\n', stdout);

	printf("After Dequeue\n");
	Node* old = pq_dequeue(&node);
	print_list(node, print_fn);
	fputc('\n', stdout);

	void(*destroy_fn)(void*) = _destroy_str_list;
	destroy_list(&old, destroy_fn);
	destroy_list(&node, destroy_fn);
	//-------------------------
}

static int _test_bst_insert_destroy() {
	mu_start();
	//-------------------------
	int(*cmp_fn)(const void*, const void*) = _compare_integers;
	BSTNode* bst = NULL;
	int num = 10;
	void* value = &num;
	bst_insert(&bst, value, cmp_fn);
	mu_check(bst->right == NULL);
	mu_check(bst->left == NULL);
	mu_check(bst != NULL);
	const int* val = bst->a_value;
	int cur_val = *val;
	mu_check(cur_val == 10);
	int num_two = 2;
	value = &num_two;
	bst_insert(&bst, value, cmp_fn);
	mu_check(bst->left != NULL);
	val = bst->left->a_value;
	cur_val = *val;
	mu_check(cur_val == 2);
	int num_three = 20;
	value = &num_three;
	bst_insert(&bst, value, cmp_fn);
	mu_check(bst->right != NULL);
	val = bst->right->a_value;
	cur_val = *val;
	mu_check(cur_val == 20);
	int num_four = 1;
	value = &num_four;
	bst_insert(&bst, value, cmp_fn);
	mu_check(bst->left->left != NULL);
	val = bst->left->left->a_value;
	cur_val = *val;
	mu_check(cur_val == 1);
	int num_five = 8;
	value = &num_five;
	bst_insert(&bst, value, cmp_fn);
	mu_check(bst->left->right != NULL);
	val = bst->left->right->a_value;
	cur_val = *val;
	mu_check(cur_val == 8);
	int num_six = 7;
	value = &num_six;
	bst_insert(&bst, value, cmp_fn);
	int num_sev = 11;
	value = &num_sev;
	bst_insert(&bst, value, cmp_fn);
	int num_eight = 11;
	value = &num_eight;
	bst_insert(&bst, value, cmp_fn);
	int num_nine = 20000000;
	value = &num_nine;
	bst_insert(&bst, value, cmp_fn);

	printf("Testing Print BST\n");
	void(*print_fn)(const void*) = _print_integer;
	print_tree(bst, print_fn);
	fputc('\n', stdout);
	
	void(*destroy_fn)(void*) = _destroy_int_list;
	destroy_tree(&bst, destroy_fn);
	//-------------------------
	mu_end();
}

static void _test_bst_insert_w_string() {
	void(*destroy_fn)(void*) = _destroy_str_list;
	int(*cmp_fn)(const void*, const void*) = _compare_strings;
	void(*print_fn)(const void*) = _print_string;
	//-------------------------
	BSTNode* bst = NULL;
	bst_insert(&bst, _copy_str("Hello"), cmp_fn);
	bst_insert(&bst, _copy_str("A"), cmp_fn);
	bst_insert(&bst, _copy_str("AB"), cmp_fn);
	bst_insert(&bst, _copy_str("LONGEST WORD IN THIS LIST"), cmp_fn);
	bst_insert(&bst, _copy_str("LONGEST WORD IN THIS LIST"), cmp_fn);
	bst_insert(&bst, _copy_str("Why is it working"), cmp_fn);

	print_tree(bst, print_fn);
	destroy_tree(&bst, destroy_fn);
	//-------------------------
}

int main(int argc, char* argv[]) {

	mu_run(_test_stack_push_pop);
	_test_pq_enqueue_dequeue();
	_test_string_enqueue_dequeue();
	mu_run(_test_bst_insert_destroy);
	_test_bst_insert_w_string();
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

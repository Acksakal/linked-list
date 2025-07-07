/**
 * Linked List Library
 * 
 * @file llist.h
 * @author Acksakal
 * @date Monday July 7th, 2025.
 * 
 */

#include <stdbool.h>

/**
 * A node is a linked list
 * 
 */
typedef struct node
{
    int value; /**< the value stored in the node */
    struct node *next; /**< pointer to the next node in the list */
} Node;

void print_list(Node *);
Node *insert_at_head(Node *, int);
Node *insert_at_tail(Node *, int);
Node *delete_at_head(Node *);
Node *delete_at_tail(Node *);
Node *delete_first_match(Node *, int delete_value, bool *was_deleted);
Node *delete_all_matches(Node *, int delete_value, int *num_deleted);
Node *efficient_delete_match(Node *, int delete_value, int *num_deleted);
Node *append_list(Node *head1, Node *head2);
Node *reverse_list(Node *head);
size_t length(Node *);
size_t recursive_length(Node *);
bool is_member(Node *node, int value_to_find);
int count_matches(Node *node, int value_to_find);
void replace_matches(Node *node, int find_value, int replace_value);
void sort_list(Node *head);
void sort_list_inef(Node *head);
void remove_duplicates(Node *head);
Node *insert_after(Node *, int, int);
Node *delete_list(Node *node);
void sum_lists(Node *node1, Node *node2);
Node *duplicate_list(Node *);
Node *merge_sorted_lists(Node *node1, Node *node2);
Node *merge_sorted_lists_dummied(Node *node1, Node *node2);
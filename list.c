#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

void print_list(Node *);
Node *insert_at_head(Node *, int);
Node *insert_at_tail(Node *, int);
Node *delete_at_head(Node *);
Node *delete_at_tail(Node *);
Node *delete_first_match(Node *, int delete_value, bool *was_deleted);
Node *delete_all_matches(Node *, int delete_value, int *num_deleted);
Node *efficient_delete_match(Node *, int delete_value, int *num_deleted);
size_t length(Node *);
size_t recursive_length(Node *);
bool is_member(Node *node, int value_to_find);
int count_matches(Node *node, int value_to_find);
void replace_matches(Node *node, int find_value, int replace_value);

int main()
{
    Node *list8 = NULL; /* an empty list */

    list8 = insert_at_head(list8, 4);
    list8 = insert_at_head(list8, 3);
    list8 = insert_at_head(list8, 4);
    list8 = insert_at_head(list8, 5);
    list8 = insert_at_head(list8, 4);
    list8 = insert_at_head(list8, 4);
    list8 = insert_at_head(list8, 7);
    list8 = insert_at_head(list8, 4);
    list8 = insert_at_head(list8, 4);

    printf("List before delete...\n");
    print_list(list8);
    int num_deleted = 0;
    list8 = efficient_delete_match(list8, 4, &num_deleted);
    printf("\nList after delete...\n");
    print_list(list8);
    printf("Numbers of elements deleted: %d\n", num_deleted);

    Node *list9 = NULL, *list10 = NULL;
    for (int i = 0; i < 500000; i++)
        list9 = insert_at_head(list9, i % 10);

    for (int i = 0; i < 500000; i++)
        list10 = insert_at_head(list10, i % 10);

    clock_t tic, toc;
    tic = clock();
    list9 = delete_all_matches(list9, 4, &num_deleted);
    toc = clock();
    printf("delete_all_matches: %fs\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    printf("elements deleted: %d\n", num_deleted);

    tic = clock();
    list10 = efficient_delete_match(list10, 4, &num_deleted);
    toc = clock();
    printf("efficient_delete_all_matches: %fs\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    printf("elements deleted: %d\n", num_deleted);

    /*
    delete_all_matches: 21.178000s -> too long!
    elements deleted: 50000
    efficient_delete_all_matches: 0.002000s -> faster than an eye blink
    elements deleted: 50000
    */
}

void print_list(Node *head)
{
    Node *current;
    current = head;
    size_t i = 0;
    while (current != NULL)
    {
        printf("Node %zu: %d\n", i++, current->value);
        current = current->next;
    }
}

Node *insert_at_head(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = new_value;
    if (head != NULL)
        new_node->next = head;

    return new_node;
}

Node *insert_at_tail(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = new_value;
    if (head == NULL)
        return new_node;
    else
    {
        Node *current = head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
        return head;
    }
}

Node *delete_at_head(Node *head)
{
    if (head == NULL)
        return NULL;
    else
    {
        Node *new_head = head->next;
        free(head);
        return new_head;
    }
}

Node *delete_at_tail(Node *head)
{
    if (head == NULL)
        return NULL;
    else if (head->next == NULL)
    {
        free(head);
        return NULL;
    }

    Node *current = head;
    while (current->next->next != NULL)
        current = current->next;

    free(current->next);
    current->next = NULL;
    return head;
}

/* This is gonna be inefficient for large datasets */
Node *delete_all_matches(Node *head, int delete_value, int *num_deleted)
{
    Node *current = head;
    bool deleted = false;
    *num_deleted = 0;

    do
    {
        current = delete_first_match(current, delete_value, &deleted);
        if (deleted)
            *num_deleted += 1;
    } while (deleted);

    return current;
}

Node *efficient_delete_match(Node *head, int delete_value, int *num_deleted)
{
    if (head == NULL)
        return NULL;

    Node *current, *temp, *new_head;
    current = head;
    *num_deleted = 0;

    while (current->value == delete_value)
    {
        temp = current;
        current = current->next;
        free(temp);
        *num_deleted += 1;

        if (current == NULL)
            return NULL;
    }

    new_head = current;

    while (current->next != NULL)
    {
        if (current->next->value == delete_value)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            *num_deleted += 1;
        }
        else
            current = current->next;
    }
    return new_head;
}

Node *delete_first_match(Node *head, int delete_value, bool *was_deleted)
{
    if (head == NULL)
    {
        *was_deleted = false;
        return NULL;
    }

    if (head->value == delete_value)
    {
        Node *new_head = head->next;
        free(head);
        *was_deleted = true;
        return new_head;
    }

    Node *prev = head;
    Node *current = head->next;
    while (current != NULL)
    {
        if (current->value == delete_value)
        {
            prev->next = current->next;
            free(current);
            *was_deleted = true;
            return head;
        }
        prev = current;
        current = current->next;
    }

    *was_deleted = false;
    return head;
}

size_t length(Node *head)
{
    size_t len = 0;
    Node *current = head;
    while (current != NULL)
    {
        len++;
        current = current->next;
    }

    return len;
}

size_t recursive_length(Node *head)
{
    if (head == NULL)
        return 0;
    else
        return 1 + recursive_length(head->next);
}

bool is_member(Node *node, int value_to_find)
{
    if (node == NULL)
        return false;
    else if (node->value == value_to_find)
        return true;

    return is_member(node->next, value_to_find);
}

int count_matches(Node *node, int value_to_find)
{
    if (node == NULL)
        return 0;
    else if (node->value == value_to_find)
        return 1 + count_matches(node->next, value_to_find);

    return count_matches(node->next, value_to_find);
}

void replace_matches(Node *node, int find_value, int replace_value)
{
    if (node != NULL)
    {
        if (node->value == find_value)
        {
            node->value = replace_value;
        }

        replace_matches(node->next, find_value, replace_value);
    }
}

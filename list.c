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

int main()
{
    Node *list4 = NULL;
    list4 = insert_at_head(list4, 5);
    list4 = insert_at_head(list4, 5);
    list4 = insert_at_head(list4, 6);
    list4 = insert_at_head(list4, 7);
    list4 = insert_at_head(list4, 5);
    list4 = insert_at_head(list4, 8);
    list4 = insert_at_head(list4, 1);
    list4 = insert_at_head(list4, 6);
    list4 = insert_at_head(list4, 2);
    list4 = insert_at_head(list4, 8);
    list4 = insert_at_head(list4, 9);
    list4 = insert_at_head(list4, 7);
    list4 = insert_at_head(list4, 2);
    list4 = insert_at_head(list4, 6);
    puts("Before");
    print_list(list4);
    remove_duplicates(list4);
    puts("After");
    print_list(list4);
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

Node *append_list(Node *head1, Node *head2)
{
    if (head1 == NULL)
        return head2;

    Node *current = head1;
    while (current->next != NULL)
        current = current->next;
    current->next = head2;
    return head1;
}

Node *reverse_list(Node *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;

    Node *current = head;
    Node *next_node = head->next;

    current->next = NULL;

    while (next_node != NULL)
    {
        Node *temp = next_node->next;
        next_node->next = current;
        current = next_node;
        next_node = temp;
    }

    return current;
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

void sort_list(Node *head)
{
    if (head == NULL || head->next == NULL)
        return;

    bool swapped = false;
    Node *end = NULL;

    do
    {
        swapped = false;
        Node *current = head;
        Node *prev = NULL;

        while (current->next != end)
        {
            if (current->value > current->next->value)
            {
                int temp;
                temp = current->value;
                current->value = current->next->value;
                current->next->value = temp;
                swapped = true;
            }
            current = current->next;
        }
        end = current;

    } while (swapped);
}

void sort_list_inef(Node *head)
{
    if (head == NULL || head->next == NULL)
        return;

    bool swapped = false;

    do
    {
        swapped = false;
        Node *current = head;
        Node *prev = NULL;
        while (current->next != NULL)
        {
            prev = current;
            current = current->next;
            if (current != NULL)
            {
                if (current->value < prev->value)
                {
                    int temp;
                    temp = prev->value;
                    prev->value = current->value;
                    current->value = temp;
                    swapped = true;
                }
            }
        }
    } while (swapped);
}

void remove_duplicates(Node *head)
{
    if (head == NULL || head->next == NULL)
        return;

    Node *current1, *current2, *duplicate;
    current1 = head;

    while (current1 != NULL && current1->next != NULL)
    {
        current2 = current1;

        while (current2->next != NULL)
        {
            if (current1->value == current2->next->value)
            {
                duplicate = current2->next;
                current2->next = current2->next->next;
                free(duplicate);
            }
            else
            {
                current2 = current2->next;
            }
        }
        current1 = current1->next;
    }
}
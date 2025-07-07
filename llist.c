/**
 * @file llist.c
 * @author Acksakal
 * @date Monday July 7th, 2025. 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

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

Node *insert_after(Node *head, int new_value, int after_value)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = new_value;

    if (head == NULL)
        return new_node;
    else
    {
        Node *current = head;
        while (current->next != NULL)
        {
            if (current->value == after_value)
            {
                new_node->next = current->next;
                current->next = new_node;
                return head;
            }
            else
                current = current->next;
        }

        /* If no value is found append the new_node to the tail */
        new_node->next = current->next;
        current->next = new_node;
        return head;
    }
}

Node *delete_list(Node *node)
{
    if (node != NULL)
    {
        delete_list(node->next);
        free(node);
    }
    return NULL;
}

void sum_lists(Node *list1, Node *list2)
{
    if (list1 == NULL || list2 == NULL)
        return;
    list1->value += list2->value;
    sum_lists(list1->next, list2->next);
}

Node *duplicate_list(Node *node)
{
    if (node == NULL)
        return NULL;

    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = node->value;

    new_node->next = duplicate_list(node->next);
    return new_node;
}

Node *merge_sorted_lists(Node *list1, Node *list2)
{
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;

    Node *l1current, *l2current, *new_head, *new_head_current;
    l1current = list1;
    l2current = list2;

    if (l1current->value <= l2current->value)
    {
        new_head = l1current;
        l1current = l1current->next;
    }
    else
    {
        new_head = l2current;
        l2current = l2current->next;
    }

    new_head_current = new_head;

    while (l1current != NULL && l2current != NULL)
    {

        if (l1current->value <= l2current->value)
        {
            new_head_current->next = l1current;
            new_head_current = new_head_current->next;
            l1current = l1current->next;

        }
        else
        {
            new_head_current->next = l2current;
            new_head_current = new_head_current->next;
            l2current = l2current->next;
        }
    }

    if (l1current == NULL) new_head_current->next = l2current;
    else if (l2current == NULL) new_head_current->next = l1current;

    return new_head;
}

/**
 * Merges two sorted lists (lowest to highest) into a single sorted list.
 * 
 * @param pointer to head of the first list
 * @param pointer to head of the second list
 * @return pointer to head of the merged list
 * 
 */
Node *merge_sorted_lists_dummied(Node *list1, Node *list2) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->value <= list2->value) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    tail->next = (list1 != NULL) ? list1 : list2;
    return dummy.next;
}
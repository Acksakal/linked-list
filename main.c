#include <stdio.h>
#include "llist.h"

int main()
{
    Node *list1 = NULL, *list2 = NULL, *list3 = NULL;
    list1 = insert_at_tail(list1, 1);
    list1 = insert_at_tail(list1, 2);
    list1 = insert_at_tail(list1, 3);
    list1 = insert_at_tail(list1, 8);
    list2 = insert_at_tail(list2, 4);
    list2 = insert_at_tail(list2, 5);
    list2 = insert_at_tail(list2, 6);
    list2 = insert_at_tail(list2, 18);
    list2 = insert_at_tail(list2, 19);
    print_list(list1);
    puts("");
    print_list(list2);
    list3 = merge_sorted_lists_dummied(list1, list2);
    puts("");
    print_list(list3);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "llist.h"

int main()
{
    srand(time(NULL));
    Node *list11 = NULL;
    for (int i = 0; i < 10; i++) {
        list11 = insert_at_head(list11, rand() % 99);
    }
    sort_list(list11);
    list11 = insert_at_head(list11, 5);
    list11 = insert_at_head(list11, 5);
    print_list(list11);
    return 0;
}

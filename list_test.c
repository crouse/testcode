#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

struct foo {
    int info;
    struct list_head list_member;
};

void add_node(int arg, struct list_head *head)
{
    struct foo *fooPtr = (struct foo *)malloc(sizeof(struct foo));
    assert(fooPtr != NULL);
    fooPtr->info = arg;
    INIT_LIST_HEAD(&fooPtr->list_member);
    list_add(&fooPtr->list_member, head);
}

void display(struct list_head *head)
{
    struct list_head *iter;
    struct foo *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct foo, list_member);
        printf("%d ", objPtr->info);
    }
    printf("\n");
}

int main()
{
    LIST_HEAD(fooHead);
    add_node(1, &fooHead);
    add_node(2, &fooHead);
    add_node(3, &fooHead);
    add_node(4, &fooHead);
    while(1) {
        display(&fooHead);
        sleep(1);
    }
    return 0;
}


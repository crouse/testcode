#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "list.h"

#define CLEN 31

struct foo {
    int id;
    time_t time;
    struct list_head list_member;
};

void add_node(int arg, struct list_head *head)
{
    struct foo *fooPtr = (struct foo *)malloc(sizeof(struct foo));
    assert(fooPtr != NULL);
    fooPtr->id = arg;
    fooPtr->time = time(NULL);
    INIT_LIST_HEAD(&fooPtr->list_member);
    list_add(&fooPtr->list_member, head);
}

void display(struct list_head *head)
{
    struct list_head *iter;
    struct foo *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct foo, list_member);
        printf("%d", objPtr->id);
        printf("[%lu]\n", objPtr->time);
    }
    printf("\n");
}

int find_first_and_delete(int arg, struct list_head *head)
{
    struct list_head *iter;
    struct foo *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct foo, list_member);
        if(objPtr->id == arg) {
            list_del(&objPtr->list_member);
            free(objPtr);
            return 1;
        }
    }

    return 0;
}

void delete_all(struct list_head *head)
{
    struct list_head *iter;
    struct foo *objPtr;

redo:
    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct foo, list_member);
        list_del(&objPtr->list_member);
        free(objPtr);
        goto redo;
    }
}

int main()
{
    LIST_HEAD(fooHead);
    add_node(1, &fooHead);
    add_node(2, &fooHead);
    add_node(3, &fooHead);
    add_node(1, &fooHead);
    add_node(4, &fooHead);
    //find_first_and_delete(1, &fooHead);
    display(&fooHead);
    delete_all(&fooHead);
    return 0;
}


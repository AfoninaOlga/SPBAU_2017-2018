#ifndef _CLIST_12112014_
#define _CLIST_12112014_
#include <stddef.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list {
    intrusive_node head;
} intrusive_list;

void init_list(intrusive_list *);

void add_node(intrusive_list *, intrusive_node *);

void remove_node(intrusive_list *, intrusive_node *);

int get_length(intrusive_list *);

void apply(intrusive_list *lst, void (*op)(intrusive_node*, void*), void* smth);

#endif

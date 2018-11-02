#include <stdlib.h>
#include <stddef.h>
#include "clist.h"

void init_list(struct intrusive_list *list) {
	list->head = NULL;
}

void add_node(struct intrusive_list *list, struct intrusive_node *node) {
	if (list->head == NULL) {
		list->head = node;
		node->prev = NULL;
		node->next = NULL;
	} else {
		node->next = list->head;
		node->prev = NULL;
		list->head->prev = node;
		list->head = node;
	}
}

void remove_node(struct intrusive_list *list, struct intrusive_node *node) {
	if (list->head == node) {
		list->head = node->next;
	}
	if (node->prev) {
		node->prev->next = node->next;
	}
	if (node->next) {
		node->next->prev = node->prev;
	}
}

int get_length(struct intrusive_list *list) {
	int counter = 0;
	struct intrusive_node *node = list->head;
	while (node) {
		node = node->next; 
		++counter;
	}
	return counter;
}

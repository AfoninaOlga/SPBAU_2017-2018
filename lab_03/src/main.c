#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "clist.h"

struct position_node {
	int x, y;
	struct intrusive_node node;
};

void remove_position(struct intrusive_list *list, int x, int y) {
	struct intrusive_node *node = list->head;
	struct intrusive_node *next;
	struct position_node *pos;
	while (node) {
		next = node->next;
		pos = container_of(node, struct position_node, node);
		if (pos->x == x && pos->y == y) {
			remove_node(list, node);
			free(pos);
		}
		node = next;
	}
}

void add_position(struct intrusive_list *list, int x, int y) {
	struct position_node *pos = malloc(sizeof(struct position_node));
	pos->x = x;
	pos->y = y;
	add_node(list, &(pos->node));
}

void show_all_positions(struct intrusive_list *list) {
	struct intrusive_node *node = list->head;
	struct position_node *pos;
	while (node) {
		pos = container_of(node, struct position_node, node);
		printf("(%i %i) ", pos->x, pos->y);
		node = node->next;
	}
	printf("\n");
}

void remove_all_positions(struct intrusive_list *list) {
	struct intrusive_node *node = list->head;
	struct position_node *pos;
	struct intrusive_node *next;
	while (node) {
		next = node->next;
		pos = container_of(node, struct position_node, node);
		remove_node(list, node);
		free(pos);
		node = next;
	}
}

int main() {
	struct intrusive_list l;
	init_list(&l);
	char s[73];
	int x, y;
	scanf("%s", s);
	while (strcmp(s, "exit")) {
		if (!strcmp(s, "add")) {
			scanf("%i %i", &x, &y);
			add_position(&l, x, y);
		} else if (!strcmp(s, "len")) {
			printf("%i\n", get_length(&l));
		} else if (!strcmp(s, "rm")) {
			scanf("%i %i", &x, &y);
			remove_position(&l, x, y);
		} else if (!strcmp(s, "rma")) {
			remove_all_positions(&l);
		} else if (!strcmp(s, "print")) {
			show_all_positions(&l);
		} else {
			printf("Unknown command\n");
		}
		scanf("%s", s);
	}
	remove_all_positions(&l);
	return 0;
}

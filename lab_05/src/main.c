#include <stdio.h>
#include <string.h>
#include "position.h"

void loadtext(char *filename, intrusive_list *l) {
   FILE *f = fopen(filename, "rt");
   int x = 0, y = 0;
   while (fscanf(f, "%d %d", &x, &y) == 2) {
       add_position(l, x, y);
   }
   fclose(f);
}

void loadbin(char *filename, intrusive_list *l) {
   FILE *f = fopen(filename, "rb");
   int x = 0, y = 0;
   while (fread(&x, 3, 1, f) && fread(&y, 3, 1, f)) {
       add_position(l, x, y);
   }
   fclose(f);
}

void print(intrusive_node* node, void* format) {
    char *form = (char*)format;
    position_node *pnode = container_of(node, position_node, node);
    printf(form, pnode->x, pnode->y);
}

void count(intrusive_node *node, void* num) {
    int* n = (int*)num;
    (*n)++;
}

void savetext(intrusive_node *node, void* file) {
    FILE *f = (FILE*)file;
    position_node *pnode = container_of(node, position_node, node);
    fprintf(f, "%d %d\n", pnode->x, pnode->y);
}

void savebin(intrusive_node *node, void* file) {
    FILE *f = (FILE*)file;
    position_node *pnode = container_of(node, position_node, node);
    fwrite(&pnode->x, 3, 1, f);
    fwrite(&pnode->y, 3, 1, f);
}

int main(int argc, char **argv) {
    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);
    int num = 0;
    if (strcmp(argv[1], "loadtext") == 0) {
        loadtext(argv[2], l);
    } else if (strcmp(argv[1], "loadbin") == 0) {
        loadbin(argv[2], l);
    }
    if (strcmp(argv[3], "print") == 0) {
        apply(l, &print, argv[4]);
    } else if (strcmp(argv[3], "count") == 0) {
        apply(l, &count, &num);
        printf("%i\n", num);
    } else if (strcmp(argv[3], "savetext") == 0) {
        FILE *f = fopen(argv[4], "wt");
        apply(l, &savetext, f);
        fclose(f);
    } else if (strcmp(argv[3], "savebin") == 0) {
        FILE *f = fopen(argv[4], "wb");
        apply(l, &savebin, f);
        fclose(f);
    }
    delete_all(l);
    return 0;
}


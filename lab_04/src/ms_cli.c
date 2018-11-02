#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mergesort.h"

int compare_int(const void *a, const void *b) {
    const int *pa = a;
    const int *pb = b;
    if (*pa > *pb) return 1;
    if (*pa < *pb) return -1;
    return 0;
}

int compare_char(const void* a, const void* b) {
	const char *pa = a;
	const char *pb = b;
    if(*pa > *pb) return 1;
    if(*pa < *pb) return -1;
    return 0;
}

int compare_str(const void* a, const void* b) {
	return strcmp(*(const char**)a, *(const char**)b);
}

int main(int argc, char **argv) {
	if (strcmp(argv[1], "int") == 0) {
		int *data = (int*)malloc(sizeof(int) * (argc - 2));
		for (int i = 0; i < argc - 2; ++i)
			data[i] = atoi(argv[i + 2]);
		mergesort(data, argc - 2, sizeof(int), compare_int);
		for (int i = 0; i < argc - 2; i++)
			printf("%i ", data[i]);
		free(data);
	}
	if (strcmp(argv[1], "char") == 0) {
		char *data = (char*)malloc(sizeof(char) * (argc - 2));
		for (int i = 0; i < argc - 2; ++i)
			data[i] = argv[i + 2][0];
		mergesort(data, argc - 2, sizeof(char), compare_char);
		for (int i = 0; i < argc - 2; i++)
			printf("%c ", data[i]);
		free(data);
	}
	if (strcmp(argv[1], "str") == 0) {
		char **data = (char**)malloc(sizeof(char*) * (argc - 2));
		for (int i = 0; i < argc - 2; ++i)
			data[i] = argv[i + 2];
		mergesort(data, argc - 2, sizeof(char*), compare_str);
		for (int i = 0; i < argc - 2; i++)
			printf("%s ", data[i]);
		free(data);
	}
}

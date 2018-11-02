#include <stdlib.h>

#ifndef __MERGESORT_H_
#define __MERGESORT_H_

void copy(char *base, char *buffer, size_t num);

void merge(size_t l, size_t m, size_t r, char *base, char *buffer, size_t size, int(*compar)(const void *, const void *));
    
void sort(size_t l, size_t r, char *base, char *buffer, size_t size, int(*compar)(const void *, const void *));

int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));

#endif

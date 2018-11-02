#include <stdlib.h>
#include <stdio.h>

void copy(char *base, char *buffer, size_t num) {
    size_t i;
    for (i = 0; i < num; ++i) {
        buffer[i] = base[i];
    }
}

void merge(size_t l, size_t m, size_t r, char *base, char *buffer, size_t size, int(*compar)(const void *, const void *)) {
    size_t p1 = l;
    size_t p2 = m;
    size_t i = l;
    while (p1 < m && p2 < r) {
        if (compar(base + p1 * size, base + p2 * size) < 0) {
            copy(base + p1 * size, buffer + i * size, size);
            p1++;
        } else {
            copy(base + p2 * size, buffer + i * size, size);
            p2++;
        }
        i++;
    }
    if (p1 < m) copy(base + p1 * size, buffer + i * size, (m - p1) * size);
    if (p2 < r) copy(base + p2 * size, buffer + i * size, (r - p2) * size);
    copy(buffer + l * size, base + l * size, (r - l) * size);
}

void sort(size_t l, size_t r, char *base, char *buffer, size_t size, int(*compar)(const void *, const void *)) {
    if (r - l <= 1) return;
    size_t m = (l + r) / 2;
    sort(l, m, base, buffer, size, compar);
    sort(m, r, base, buffer, size, compar);
    merge(l, m, r, base, buffer, size, compar);
}

int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*)) {
	char *buffer = (char*)malloc(num * size);
	if (buffer == NULL)
		return -1;
	sort(0, num, base, buffer, size, compar);
	free(buffer);
	return 0;
}

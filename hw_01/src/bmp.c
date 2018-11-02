#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bmp.h"

#pragma pack(push, 1)

typedef struct infoheader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pels_per_meter;
    int32_t y_pels_per_meter;
    uint32_t clr_used;
    uint32_t clr_important;
} infoheader;

typedef struct fileheader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t off_bits;
} fileheader;

#pragma pack(pop)

typedef struct pixel {
    char r;
    char g;
    char b;
} pixel;

typedef struct bmp_image {
    pixel **pic;
    infoheader info_head;
    fileheader file_head;
    int w;
    int h;
} bmp_image;

pixel ** arr_pixel(int w, int h) {
    pixel **arr = (pixel**)malloc(h * sizeof(pixel*));
    pixel *line = (pixel*)malloc(w * h * sizeof(pixel));
    if (arr == NULL || line == NULL)
        return NULL;
    for (int i = 0; i < h; ++i) {
        arr[i] = line + i * w;
    }
    return arr;
}

bmp_image * load_bmp(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Cannot open file");
        return NULL;
    }
    
    bmp_image *bmp_im = (bmp_image*)malloc(sizeof(bmp_image));
    if (bmp_im == NULL) {
        printf("Not enough memory");
        return NULL;
    }
    
    fread(&bmp_im->file_head, sizeof(fileheader), 1, f);
    fread(&bmp_im->info_head, sizeof(infoheader), 1, f);
    
    bmp_im->w = bmp_im->info_head.width;
    bmp_im->h = bmp_im->info_head.height;
    
    pixel **arr = arr_pixel(bmp_im->w, bmp_im->h);
    int cnt_null = (4 - ((3 * bmp_im->w) % 4)) % 4;
    pixel null_pix = {0, 0, 0};
    for (int i = 0; i < bmp_im->h; ++i) {
        fread(arr[bmp_im->h - i - 1], sizeof(pixel), bmp_im->w, f);
        fread(&null_pix, cnt_null, 1, f);
    }
    bmp_im->pic = arr;
    
    fclose(f);
    
    return bmp_im;
}

int crop(bmp_image *bmp_im, int x, int y, int w, int h) {
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > bmp_im->w || y + h > bmp_im->h) {
        printf("Wrong parametrs");
        return -1;
    }
    
    bmp_im->w = w;
    bmp_im->h = h;
    
    pixel **arr = arr_pixel(bmp_im->w, bmp_im->h);
    
    if (arr == NULL) {
        printf("Not enough memory");
        return 1;
    }
    
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            arr[i][j] = bmp_im->pic[i + y][j + x];
        }
    }
    free(bmp_im->pic[0]);
    free(bmp_im->pic);
    bmp_im->pic = arr;
    
    return 0;
}

int rotate(bmp_image *bmp_im) {
    pixel **arr = arr_pixel(bmp_im->h, bmp_im->w);
    
    if (arr == NULL) {
        printf("Not enough memory");
        return -1;
    }
    
    for (int i = 0; i < bmp_im->h; ++i) {
        for (int j = 0; j < bmp_im->w; ++j) {
            arr[j][bmp_im->h - i - 1] = bmp_im->pic[i][j];
        }
    }
    free(bmp_im->pic[0]);
    free(bmp_im->pic);
    bmp_im->pic = arr;
    
    int w = bmp_im->w;
    bmp_im->w = bmp_im->h;
    bmp_im->h = w;
    
    return 0;
}

int save_bmp(const char* filename, bmp_image *bmp_im) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Cannot open file");
        return -1;
    }
    
    bmp_im->info_head.width = bmp_im->w;
    bmp_im->info_head.height = bmp_im->h;
    
    int cnt_null = (4 - ((3 * bmp_im->w) % 4)) % 4;
    bmp_im->info_head.size_image = 3 * bmp_im->w * bmp_im->h + bmp_im->h * cnt_null;
    bmp_im->file_head.size = bmp_im->file_head.off_bits + bmp_im->info_head.size_image;
    
    fwrite(&bmp_im->file_head, sizeof(fileheader), 1, f);
    fwrite(&bmp_im->info_head, sizeof(infoheader), 1, f);
    
    pixel null_pix = {0, 0, 0};
    for (int i = bmp_im->info_head.height - 1; i >= 0 ; --i) {
        fwrite(bmp_im->pic[i], sizeof(pixel), bmp_im->info_head.width, f);
        fwrite(&null_pix, cnt_null, 1, f);
    }
    
    fclose(f);
    
    return 0;
}

void clear_all(bmp_image *bmp_im) {
    free(bmp_im->pic[0]);
    free(bmp_im->pic);
    free(bmp_im);
}

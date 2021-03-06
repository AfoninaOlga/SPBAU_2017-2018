#ifndef _BMP_
#define _BMP_

typedef struct bmp_image bmp_image;

void clear_all(bmp_image *bmp_im);
bmp_image * load_bmp(const char *filename);
int crop(bmp_image *bmp_im, int x, int y, int w, int h);
int rotate(bmp_image *bmp_im);
int save_bmp(const char* filename, bmp_image *bmp_im);
void clear_all(bmp_image *bmp_im);

#endif

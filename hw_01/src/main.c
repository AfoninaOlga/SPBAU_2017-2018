#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"
 
int main(int argc, char** argv) {
    if (strcmp(argv[1], "crop-rotate") == 0) {
        bmp_image *bmp_im = load_bmp(argv[2]);
        if (bmp_im == NULL) {
            return -1;
        }
        if (crop(bmp_im, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7])) != 0) {
            return -1;
        }
        if (rotate(bmp_im) != 0) {
            return -1;
        }
        if (save_bmp(argv[3], bmp_im) != 0) {
            return -1;
        }
        clear_all(bmp_im);
    }
    return 0;
}

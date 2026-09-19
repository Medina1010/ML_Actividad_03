#ifndef IMAGE_WRAPPER
#define IMAGE_WRAPPER

#include "stb_image.h"
#include "stb_image_write.h"

typedef struct {
  int width, height, channels;
  unsigned char *data;
} stbi_image;

void stbi_load_simple(char *path, stbi_image *image, int channels);
void stbi_write_png_simple(char *path, stbi_image *image, int channels);

#endif // IMAGE_WRAPPER

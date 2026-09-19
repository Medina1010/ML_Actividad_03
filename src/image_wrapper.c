#include "image_wrapper.h"

void stbi_load_simple(char *path, stbi_image *image, int channels) {
  image->data = stbi_load(path, &image->width, &image->height, &image->channels,
                          channels);
}

void stbi_write_png_simple(char *path, stbi_image *image, int channels) {
  stbi_write_png(path, image->width, image->height, channels, image->data,
                 image->width * channels);
}

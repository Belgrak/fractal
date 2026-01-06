#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

// Используем uint16_t для координат и uint8_t для цвета (0-255)
typedef uint16_t pixel_coord;
typedef uint8_t pixel_data;

typedef struct image image_t;
typedef struct image *image_p;

image_p create_image(pixel_coord width, pixel_coord height);
void free_image(image_p picture);
void clear_image(image_p picture);
void fill_random(image_p picture);
void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data color);
pixel_data get_pixel(image_p picture, pixel_coord x, pixel_coord y);

int save_pgm_binary(image_p picture, const char *filename);

struct image
{
    pixel_coord width, height;
    pixel_data *data;
};

#endif
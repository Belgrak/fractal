#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "image.h"

image_p create_image(pixel_coord width, pixel_coord height)
{
    image_p v = malloc(sizeof(image_t));
    assert(v != NULL); 
    
    v->width = width;
    v->height = height;
    v->data = malloc(sizeof(pixel_data) * width * height);
    assert(v->data != NULL);

    return v;
}

void clear_image(image_p picture)
{
    memset(picture->data, 0, sizeof(pixel_data) * picture->width * picture->height);
}

void fill_random(image_p picture)
{
    pixel_data *p = picture->data;
    for(size_t z = 0; z < (size_t)picture->height * picture->width; ++z, ++p)
        *p = (pixel_data)(rand() % 255);
}

void free_image(image_p picture)
{
    if (picture) {
        free(picture->data);
        free(picture);
    }
}

/*
 * Сохранение в BINARY PGM.
 */
int save_pgm_binary(image_p picture, const char *filename)
{
    FILE *to = fopen(filename, "wb"); 
    if (!to) return -1;

    // Заголовок P5 (Binary Grayscale), ширина, высота, макс. значение
    fprintf(to, "P5\n%u %u\n255\n", picture->width, picture->height);

    size_t items = (size_t)picture->width * picture->height;
    size_t written = fwrite(picture->data, sizeof(pixel_data), items, to);
    
    // Проверяем, всё ли записалось
    assert(written == items);

    fclose(to);
    return 0;
}

void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data color)
{
    assert("Out of dimension" && x < picture->width && y < picture->height);
    
    picture->data[(size_t)picture->width * y + x] = color;
}

pixel_data get_pixel(image_p picture, pixel_coord x, pixel_coord y)
{
    assert("Out of dimension" && x < picture->width && y < picture->height);
    
    return picture->data[(size_t)picture->width * y + x];
}
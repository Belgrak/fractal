#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "image.h"

#define W 1024
#define H 1024
#define MAX_ITER 255

/* Типы фракталов */
typedef enum { MANDELBROT, JULIA, BURNING_SHIP } frac_type;

/*
 * Универсальная функция генерации
 */
void draw_fractal(image_p img, frac_type type)
{
    double min_re, max_re, min_im, max_im;

    // Настройка координат в зависимости от фрактала
    if (type == BURNING_SHIP) {
        min_re = -2.5; max_re = 1.5; min_im = -2.0; max_im = 1.0;
    } else {
        min_re = -2.0; max_re = 1.0; min_im = -1.5; max_im = 1.5;
    }
    
    double re_factor = (max_re - min_re) / (img->width - 1);
    double im_factor = (max_im - min_im) / (img->height - 1);

    // Константа для Julia
    double complex k = -0.7 + 0.27015 * I;

    for (pixel_coord y = 0; y < img->height; ++y) {
        double c_im = max_im - y * im_factor;
        
        for (pixel_coord x = 0; x < img->width; ++x) {
            double c_re = min_re + x * re_factor;
            double complex z, c;
            
            if (type == JULIA) {
                z = c_re + c_im * I;
                c = k;
            } else {
                z = 0;
                c = c_re + c_im * I;
            }

            int iter = 0;
            while (cabs(z) < 2.0 && iter < MAX_ITER) {
                if (type == BURNING_SHIP) {
                    double re = fabs(creal(z));
                    double im = fabs(cimag(z));
                    z = (re + im * I) * (re + im * I) + c;
                } else {
                    // Mandelbrot и Julia: z = z^2 + c
                    z = z * z + c;
                }
                iter++;
            }

            set_pixel(img, x, y, (pixel_data)iter);
        }
    }
}

int main(void)
{
    image_p img = create_image(W, H);

    printf("Generating Mandelbrot...\n");
    clear_image(img);
    draw_fractal(img, MANDELBROT);
    save_pgm_binary(img, "mandelbrot.pgm");

    printf("Generating Julia...\n");
    clear_image(img);
    draw_fractal(img, JULIA);
    save_pgm_binary(img, "julia.pgm");

    printf("Generating Burning Ship...\n");
    clear_image(img);
    draw_fractal(img, BURNING_SHIP);
    save_pgm_binary(img, "ship.pgm");

    free_image(img);
    printf("Done. Check .pgm files.\n");
    return 0;
}
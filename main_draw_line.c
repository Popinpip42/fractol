#include "mlx.h"
#include <stdio.h>

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_data;

int abs(int n)
{
  return n < 0 ? n : n;
}

// Function to put a pixel on the image
void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// Bresenham's Line Algorithm
void    draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (x0 != x1 || y0 != y1)
    {
        my_mlx_pixel_put(data, x0, y0, color);
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
    my_mlx_pixel_put(data, x1, y1, color); // Ensure the last pixel is drawn
}

int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    if (!mlx)
    {
        printf("Not correct init\n");
        return (-1);
    }
    else
    {
        printf("Correct init\n");
        mlx_win = mlx_new_window(mlx, 500, 500, "Line Example!");
        //Get image for double buffering
        img.img = mlx_new_image(mlx, 500, 500);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

        // Draw a line from (50, 50) to (450, 450) with red color (0x00FF0000)
        for (int i = 1; i < 100; i++) {
          draw_line(&img, 50 + i, 50, 450, 450, 0x00FF0000);
        }
        for (int i = 1; i < 100; i++) {
          draw_line(&img, 50, 50 + i, 450, 450, 0x00FF0000);
        }

        // Put the image onto the window
        mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
        mlx_loop(mlx);
    }
    printf("Successfully finished fractol program :D\n");
}

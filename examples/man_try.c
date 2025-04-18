#include "fractol.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

#define PALETTE_SIZE 4
int W = 900;
int L = 900;

typedef struct s_complex {
	double real;
	double imag;
} t_complex;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
	if (x >= 0 && x < W && y >= 0 && y < L)
	{
		char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int create_color(t_color color) {
	return (color.r << 16 | color.g << 8 | color.b);
}

int calculate_color(double smooth_iter, int max_iter, t_color *palette, int palette_size) {
	double t = smooth_iter / max_iter; // Normalize smooth_iter to [0, 1]
	double scaled_t = t * (palette_size - 1); // Scale to palette indices
	int index1 = (int)scaled_t;               // Lower bound index
	int index2 = index1 + 1;                  // Upper bound index
	double fractional = scaled_t - index1;    // Fractional part

	// Ensure indices are within bounds
	if (index2 >= palette_size) index2 = palette_size - 1;

	// Interpolate between the two palette colors
	t_color color;
	color.r = (int)((1 - fractional) * palette[index1].r + fractional * palette[index2].r);
	color.g = (int)((1 - fractional) * palette[index1].g + fractional * palette[index2].g);
	color.b = (int)((1 - fractional) * palette[index1].b + fractional * palette[index2].b);

	return create_color(color);
}

void render_mandelbrot(t_data *data, int max_iter) {
	int x, y;
	t_complex c, z;
	double smooth_iter;

	t_color palette[PALETTE_SIZE] = {
		{0, 0, 255},    // Blue
		{255, 0, 0},    // Red
		{0, 255, 0},    // Red
		{255, 255, 255} // White
	};

	for (y = 0; y < L; y++) {
		for (x = 0; x < W; x++) {
			// Map pixel coordinates to the complex plane
			c.real = (x - W / 2.0) * 4.0 / W;
			c.imag = (y - L / 2.0) * 4.0 / L;

			z.real = 0;
			z.imag = 0;

			int iter = 0;
			double z_magnitude_squared = 0;

			// Procedural iteration for Mandelbrot formula
			while (iter < max_iter && z_magnitude_squared <= 4.0) {
				double temp = z.real * z.real - z.imag * z.imag + c.real;
				z.imag = 2 * z.real * z.imag + c.imag;
				z.real = temp;
				z_magnitude_squared = z.real * z.real + z.imag * z.imag;
				iter++;
			}

			if (iter < max_iter) {
				double log_zn = log(z.real * z.real + z.imag * z.imag) / 2.0;
				double nu = log(log_zn / log(2)) / log(2);
				smooth_iter = iter + 1 - nu;
			} else {
				smooth_iter = iter;
			}

			// Calculate color based on smooth iteration count
			int color = (iter == max_iter) ? create_color((t_color){0, 0, 0})
				: calculate_color(smooth_iter, max_iter, palette, PALETTE_SIZE);

			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

int main(void) {
	void	*mlx;
	void	*mlx_window;
	t_data	data;

	mlx = mlx_init();
	if (!mlx) {
		printf("Failed to initialize MLX.\n");
		return -1;
	}

	mlx_window = mlx_new_window(mlx, W, L, "Mandelbrot Set");
	if (!mlx_window) {
		printf("Failed to create a window.\n");
		return -1;
	}

	data.img = mlx_new_image(mlx, W, L);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	render_mandelbrot(&data, 100);

	mlx_put_image_to_window(mlx, mlx_window, data.img, 0, 0);

	mlx_loop(mlx);
	return (0);
}

/*
#include "fractol.h"
#include "mlx.h"

//TODO: Implement basic window handling
//TODO: Try out implementing double buffering or other opt tech

int L = 600;
int W = 600;

// Function to put a pixel on the image
void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char    *dst;

  //data->addr : Initial position in the window
  //line_length : amount of pixels one line of the window (vertical alignment)
  //bits_per_pixel : amount of bits per pixel (Horizontal alignment)
  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int*)dst = color;
}

int	draw_square(t_data *data)
{
	int	i;
	int	j;

	i = 60;
	while (i < 120)
	{
		j = 60;
		while (j < 120)
		{
			my_mlx_pixel_put(data, i, j, 0x00FF0000);
			j++;
		}
		i++;
	}
	return (0);
}

int	threshold = 10 * pow(10, 8);
int	limit = 10 * pow(10, 8);

int	mandel_rec(int iter, t_data *data)
{
	if (iter == limit)
		return (0);
	int	tmp = iter;

	while (iter < threshold)
	{
		iter = pow(iter, 2) + iter;
	}

	if (iter < threshold)
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
	return (mandel_rec(tmp--, data));
}

void	print_mandel(t_data *data)
{
	// z -> z^2 + c;
	// c is a complex number that belong to the mandel- set if:
	// 		the iteration over z -> z^2 + c, is bounded
	// PSEUDOCODE
	// c = -1;

	int	i;

	i = 0;
	mandel_rec(i, data);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	t_data	data;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("Failed ");
		return (-1);
	}

	mlx_window = mlx_new_window(mlx, 600, 600, "First try");

	//Create a new image to render
	//We buffer the pixels into this image before "render()" call
	data.img = mlx_new_image(mlx, 600, 600);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	//draw_square(&data);
	print_mandel(&data);

	mlx_put_image_to_window(mlx, mlx_window, data.img, 0, 0);

	mlx_loop(mlx);
}
*/

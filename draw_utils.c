#include "fractol.h"

void	mlx_pixel_put_(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// Helper to interpolate between two colors
int	interpolate_color(int color1, int color2, double t)
{
	int r = ((1 - t) * ((color1 >> 16) & 0xFF)) + (t * ((color2 >> 16) & 0xFF));
	int g = ((1 - t) * ((color1 >> 8) & 0xFF)) + (t * ((color2 >> 8) & 0xFF));
	int b = ((1 - t) * (color1 & 0xFF)) + (t * (color2 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}

int	get_color(int iter, t_fractal_params *params)
{
    if (iter == params->max_iterations)
        return 0x000000; // Black for points inside Mandelbrot

    double t = (double)iter / params->max_iterations;
    t = fmod((t + params->color_offset / 255.0), 1.0); // Apply color offset

    if (params->smooth_coloring)
    {
        // Use a smooth logarithmic escape time calculation
        double zn = log(iter + 1.0) / log(params->max_iterations);
        t = fmod((zn + params->color_offset / 255.0), 1.0);
    }

    if (params->color_scheme == 1)
        return interpolate_color(0x1A1AFF, 0xFFFF00, t); // Blue → Yellow
    else if (params->color_scheme == 2)
        return interpolate_color(0x00FF00, 0xFF0000, t); // Green → Red
    else if (params->color_scheme == 3)
        return interpolate_color(0xFFFFFF, 0x000000, t); // White → Black

    return interpolate_color(0x0000FF, 0xFF00FF, t); // Default Blue → Purple
}



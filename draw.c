#include "fractol.h"

static void	draw_mandelbrot(t_data *data, t_fractal_params *params)
{
	int x, y;
	double zx, zy, cx, cy;
	int iter;

	// Calculate viewport size based on zoom
	double x_min = params->center_x - (2.0 / params->zoom);
	double x_max = params->center_x + (2.0 / params->zoom);
	double y_min = params->center_y - (1.5 / params->zoom);
	double y_max = params->center_y + (1.5 / params->zoom);

	for (y = 0; y < data->height; y++) {
		for (x = 0; x < data->width; x++) {
			cx = x_min + (x / (double)data->width) * (x_max - x_min);
			cy = y_min + (y / (double)data->height) * (y_max - y_min);
			zx = 0;
			zy = 0;
			iter = 0;

			while ((zx * zx + zy * zy) < (params->bailout_radius * params->bailout_radius)
				&& iter < params->max_iterations)
			{
				double temp = pow(zx * zx + zy * zy, params->power / 2.0) *
					cos(params->power * atan2(zy, zx)) + cx;
				zy = pow(zx * zx + zy * zy, params->power / 2.0) *
					sin(params->power * atan2(zy, zx)) + cy;
				zx = temp;
				iter++;
			}

			// Apply different color schemes, considering smooth coloring
			int color = get_color(iter, params);
			mlx_pixel_put_(data, x, y, color);
		}
	}
}

static void	draw_julia(t_data *data, t_fractal_params *params)
{
	int		x, y;
	double	c_re = params->julia_real;
	double	c_im = params->julia_i;
	double	z_re, z_im;
	double	new_re, new_im;
	int		i;

	for (y = 0; y < data->height; y++)
	{
		for (x = 0; x < data->width; x++)
		{
			z_re = ((double)x / data->width - 0.5) * 2.0 / params->zoom + params->center_x;
			z_im = ((double)y / data->height - 0.5) * 2.0 / params->zoom + params->center_y;
			i = 0;
			while (z_re * z_re + z_im * z_im <= params->bailout_radius && i < params->max_iterations)
			{
				new_re = z_re * z_re - z_im * z_im + c_re;
				new_im = 2.0 * z_re * z_im + c_im;
				z_re = new_re;
				z_im = new_im;
				i++;
			}
			mlx_pixel_put_(data, x, y, get_color(i, params));
		}
	}
}

void	draw(t_data *data)
{
	if (data->img != NULL)
		mlx_destroy_image(data->mlx, data->img);

	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
								&data->line_length, &data->endian);
	if (data->params->option == 1)
		draw_mandelbrot(data, data->params);
	else if (data->params->option == 2)
		draw_julia(data, data->params);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

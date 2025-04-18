#include "fractol.h"

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	usage_error(void)
{
	handle_error("Usage: [(1)->Mandelbrot | (2)->Julia] [c1] [c2]");
}

void	exit_program(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	free(data);
	exit(EXIT_SUCCESS);
}


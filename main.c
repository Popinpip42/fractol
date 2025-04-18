#include "fractol.h"

//TODO: import my modified fprintf
//Allowed function
//open, close, read,write,
//malloc, free,
//perror, strerror, exit

int	main(int argc, char **argv)
{
	//1- User can choose between 3 different fractals (Mandel, Julia, ...)
	//1.2 - The fractal is chosen based on execution paraemeters like : "./fractol (1..3)"
	//1.2 - Error managment if case the the parameter is invalid
	t_fractal_params	*params;
	t_data				*data;

	if (argc < 2)
		usage_error();
	params = get_params(argc, argv);
	data = get_data(900, 900);
	data->params = params;

	draw(data);

	// Set hooks
	mlx_key_hook(data->mlx_win, key_hook, data);
	mlx_mouse_hook(data->mlx_win, mouse_hook, data);
	//When pressing windows x
	mlx_hook(data->mlx_win, 17, 0, close_hook, data);

	mlx_loop(data->mlx);
}

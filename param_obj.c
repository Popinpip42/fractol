#include "fractol.h"

//TODO: write ft_atoi and ft_atof
static int	get_param_option(char *option_str)
{
	int	result;

	if (!is_valid_int(option_str))
		handle_error("Not valid option.\nChoose between 1 or 2");
	result = ft_atoi(option_str);
	if (result != 1 && result != 2)
		usage_error();
	return (result);
}

static double	get_param_julia(char *param_str)
{
	double	result;

	if (!is_valid_double(param_str))
		handle_error("Not valid julia parmaeter.");
	result = ft_atof(param_str);
	return (result);
}

t_fractal_params	*get_params(int argc, char **argv)
{
	t_fractal_params	*params;

	params = malloc(sizeof(t_fractal_params));
	if(!params)
		handle_error("get_params() malloc ERROR ===!!!");
	params->option = get_param_option(argv[1]);
	if (params->option == 2 && argc != 4)
		usage_error();
	if (params->option == 2)
	{
		params->julia_real = get_param_julia(argv[2]);
		params->julia_i = get_param_julia(argv[3]);
		printf("julia real : %f, julia imaginary: %f\n", params->julia_real, params->julia_i);
	}
	//TODO: Choose which parameters extract from this example
	params->center_x = 0.0,
	params->center_y = 0.0,
	params->zoom = 1.0,
	params->max_iterations = 100,
	params->bailout_radius = 2.0,
	params->power = 2.0,
	params->color_scheme = 2,
	params->color_offset = 10,
	params->smooth_coloring = 0;
	return (params);
}

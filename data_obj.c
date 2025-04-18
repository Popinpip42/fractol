#include "fractol.h"
#include "mlx.h"

static void	init_mlx(t_data *data, int width, int height)
{
	data->width = width;
	data->height = height;
	data->img = NULL;
	data->params = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		handle_error("mlx_init ERROR ---!!!");
	data->mlx_win = mlx_new_window(data->mlx, width, height, "lsirpa-g");
	if (!data->mlx_win)
		handle_error("mlx_win ERROR ---!!!");
}

t_data	*get_data(int width, int height)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		handle_error("get_data() malloc ERROR ===!!!");
	init_mlx(data, width, height);
	return (data);
}

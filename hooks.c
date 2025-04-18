#include "fractol.h"

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	handle_mouse(keycode, x, y, data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	handle_key(keycode, data);
	return (0);
}

int	close_hook(t_data *data)
{
	exit_program(data);
	return (0);
}

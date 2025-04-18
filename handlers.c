#include "fractol.h"

void	handle_key(int keycode, t_data *data)
{
	double	move_factor;

	//printf("Key Pressed...\n");
	//printf("Keycode : %d\n", keycode);
	move_factor = 0.1 / data->params->zoom;
	if (keycode == 53) // ESC
		exit_program(data);
	else if (keycode == 123)
		data->params->center_x -= move_factor;
		//printf("Left arrow pressed\n");
	else if (keycode == 124)
		data->params->center_x += move_factor;
		//printf("Right arrow pressed\n");
	else if (keycode == 125)
		data->params->center_y += move_factor;
		//printf("Down arrow pressed\n");
	else if (keycode == 126)
		data->params->center_y -= move_factor;
		//printf("Up arrow pressed\n");
	draw(data);
}

void	handle_mouse(int keycode, int x, int y, t_data *data)
{
	//printf("Moving mouse..\n");
	//printf("Keycode : %d, x : %d, y : %d\n", keycode, x, y);
	(void)x;
	(void)y;
	if (keycode == 1)
		data->params->zoom *= 1.1;
	else if (keycode == 2)
		data->params->zoom /= 1.1;
	
	draw(data);
}

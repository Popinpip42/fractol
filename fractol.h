#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "mlx.h"
//# define  WINDOW_L 700
//# define  WINDOW_W 700

typedef struct s_fractal_params
{
	int		option;
	double	center_x;
	double	center_y;
	double	zoom;
	int		max_iterations;
	double	bailout_radius;
	double	power;
	int		color_scheme;
	int		color_offset;
	int		smooth_coloring;
	double	julia_real;
	double	julia_i;
}	t_fractal_params;

typedef struct s_data
{
	int					height;
	int					width;
	void				*mlx;
	void				*mlx_win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	t_fractal_params	*params;
}	t_data;

//PARAMS INIT()
t_fractal_params	*get_params(int argc, char **argv);
//DATA INIT()
t_data	*get_data(int width, int height);
//ERRORS
void	handle_error(const char *message);
void	usage_error(void);
void	exit_program(t_data *data);
//EVENtS
void	handle_key(int keycode, t_data *data);
void	handle_mouse(int keycode, int x, int y, t_data *data);
//HOOKS
int		key_hook(int keycode, t_data *data);
int		close_hook(t_data *data);
int		mouse_hook(int keycode, int x, int y, t_data *data);
//DRAW
void	draw(t_data *data);
void	mlx_pixel_put_(t_data *data, int x, int y, int color);
int		interpolate_color(int color1, int color2, double t);
int		get_color(int iter, t_fractal_params *params);
//void	mlx_pixel_put_(t_data *data, int x, int y, int color);
//int		interpolate_color(int color1, int color2, double t);
//int		get_color(int iter, t_fractal_params *params);
//void	draw_mandelbrot(t_data *data, t_fractal_params *params);
//void	draw_julia(t_data *data, t_fractal_params *params);

//NUM UTILS
int		is_valid_int(const char *str);
int		is_valid_double(const char *str);
int		ft_atoi(const char *str);
double	ft_atof(const char *str);
//STR UTILS
int		ft_isdigit(int c);
int		ft_isspace(int c);

#endif

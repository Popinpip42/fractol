#include <stdio.h>
#include "mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	//void  *img;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("Not correct init\n");
		return (-1);
	}
	else{
		printf(" correct init\n");
		mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
		//1- Instantiate image Object
		img.img = mlx_new_image(mlx, 500, 500);
		//2- Load image address
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
							   &img.endian);
		//3- Paint the pixel of the image at coordinates 5, 5
		my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
		//4- Render image
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		//5- Repeat
		mlx_loop(mlx);
	}

	/* Document part_1 */
	//mlx_win = mlx_new_window(mlx, 400, 400, "Hello mlx");
	//mlx_loop(mlx);

	/* Document part_2 */
	//img = mlx_new_image(mlx, 500, 500);
	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	/*
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	*/

	printf("Succesfully finished fractol program :D\n");
}

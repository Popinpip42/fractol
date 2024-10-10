#include "fractol.h"
#include "mlx.h"

//TODO: Implement basic window handling
//TODO: Try out implementing double buffering or other opt tech

int L = 600;
int W = 600;

// Function to put a pixel on the image
void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char    *dst;

  //data->addr : Initial position in the window
  //line_length : amount of pixels one line of the window (vertical alignment)
  //bits_per_pixel : amount of bits per pixel (Horizontal alignment)
  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int*)dst = color;
}

int draw_buff(t_data *data)
{
  int i;
  int j;

  i = 60;
  while (i < 120)
  {
    j = 60;
    while (j < 120)
    {
      my_mlx_pixel_put(data, i, j, 0x00FF0000);
      j++;
    }
    i++;
  }
  return (0);
}

int main(void)
{
  void  *mlx;
  void  *mlx_window;
  t_data  data;

  mlx = mlx_init();
  if (!mlx)
  {
    printf("Failed ");
    return (-1);
  }
  mlx_window = mlx_new_window(mlx, 600, 600, "First try");

  //Create a new image to render
  //We buffer the pixels into this image before "render()" call
  data.img = mlx_new_image(mlx, 600, 600);
  data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

  draw_buff(&data);

  mlx_put_image_to_window(mlx, mlx_window, data.img, 0, 0);


  mlx_loop(mlx);
}

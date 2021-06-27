#include <stdio.h>
#include <math.h>
#include "../mlx/mlx.h"

#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF

#define VIVID_RED		0x00FF0018
#define DEEP_SAFFRON	0x00FFA52C
#define MAXIMUM_YELLOW	0x00FFFF41
#define AO				0x00008018
#define BLUE_FLAG		0x000000F9
#define PHILIPPINE_VIOLET	0x0086007D

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	add_shade(double distance, int color)
{
	return ((color & 0x00FFFFFF) | ((int)(color * (1 - distance)) & 0xFF000000));
}

int	get_opposite(int color)
{
	return (color ^ 0x00FFFFFF);
}

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_circle(t_data *data, int x, int y, int r, int color)
{
	for (int i = 0; i < 2 * r; i++)
	{
		int dy = (int)sqrt(2 * r * i - i * i);
		for (int j = -dy; j < dy ; j++)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
		}
	}
}

void	put_triangle(t_data *data, int x, int y, int a, int color)
{
	for (int i = 0; i < (int)(a * sqrt(3) / 2); i++)
	{
		for (int j = i / sqrt(3); j < a - i / sqrt(3); j++)
		{
			my_mlx_pixel_put(data, x + j, y - i, color);
		}
	}
}

void	put_rectangle(t_data *data, int x, int y, int w, int h, int color)
{
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			my_mlx_pixel_put(data, x + i, y - j, color);
		}
	}
}

void	put_lgbt(t_data *data, int x, int y, int w, int h)
{
	put_rectangle(data, x, y, w, h / 6, VIVID_RED);
	put_rectangle(data, x, y + h / 6, w, h / 6, DEEP_SAFFRON);
	put_rectangle(data, x, y + h / 3, w, h / 6, MAXIMUM_YELLOW);
	put_rectangle(data, x, y + h / 2, w, h / 6, AO);
	put_rectangle(data, x, y + 2 * h / 3, w, h / 6, BLUE_FLAG);
	put_rectangle(data, x, y + 5 * h / 6, w, h / 6, PHILIPPINE_VIOLET);
}

int main()
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 1920, 1080, "test1");
	img.img = mlx_new_image(mlx, 1920, 1080);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 700, 700, GREEN);
	put_triangle(&img, 500, 500, 200, RED);
	put_rectangle(&img, 900, 500, 100, 200, BLUE);
	put_circle(&img, 1200, 400, 100, GREEN);
	put_lgbt(&img, 10, 500, 500, 250);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

#include "../includes/fractol.h"

#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF

#define VIVID_RED		0x00FF0018
#define DEEP_SAFFRON	0x00FFA52C
#define MAXIMUM_YELLOW	0x00FFFF41
#define AO				0x00008018
#define BLUE_FLAG		0x000000F9
#define PHILIPPINE_VIOLET	0x0086007D

#define SCREEN_RED		0xCCCC0000
#define SCREEN_GREEN	0xCC00CC00
#define SCREEN_BLUE		0xCC0000CC

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

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return ((int)vars);
}


int	close_win(int keycode, t_vars *vars)
{
	printf("Farewell, friend!\n\n");
	exit(0);
	(void)vars;
	return (keycode);
}

int main()
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "win1");
	vars.data = &img;

	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0L, close_win, &vars);


	img.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);

	mandelbrot(&img);
//	julia(&img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	mlx_loop(vars.mlx);
	return (0);
}

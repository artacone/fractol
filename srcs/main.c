#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../dymlx/mlx.h"

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

typedef struct s_data
{
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

void	flood_fill_screen(t_data *data, int color)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			my_mlx_pixel_put(data, i, j, color);
		}
	}
}

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*data;
	int		x;
	int		y;
}	t_vars;

time_t start;

#define STEP 10
int	key_hook(int keycode, t_vars *vars)
{
	start = time(NULL);
	printf("Pressed key %d!\n", keycode);
	switch (keycode)
	{
		case 13:
			vars->y -= STEP;
			break ;
		case 1:
			vars->y += STEP;
			break ;
		case 0:
			vars->x -= STEP;
			break ;
		case 2:
			vars->x += STEP;
			break ;
	}
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return ((int)vars);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	printf("Mouse button %d was pressed at coordinates x=%d; y=%d!\n", button, x, y);
	(void)vars;
	return (button);
}

int	mouse_hook_on_motion(int x, int y, t_vars *vars)
{
	if (0 <= x && x <= 1920 && 0 <= y && y <= 1080)
	{
		printf("Mouse moving at %dx%d.\n", x, y);
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

int	hello_win(int keycode, t_vars *vars)
{
	printf("Hello!\n");
	(void)vars;
	return (keycode);
}

int	bye_win(int keycode, t_vars *vars)
{
	printf("Bye!\n");
	(void)vars;
	return (keycode);
}

int	release_key(int keycode, t_vars *vars)
{


	time_t key_pressed_time = time(NULL) - start;
	if (key_pressed_time > 5)
	{
		printf("RELEASE THE KEY %d!\n", keycode);
	}
	return ((int)vars);
}

int	render_next_frame(t_vars *vars)
{
	int screen_color;

	switch (time(NULL) % 3)
	{
		case 0:
			screen_color = SCREEN_RED;
			break ;
		case 1:
			screen_color = SCREEN_BLUE;
			break ;
		case 2:
			screen_color = SCREEN_GREEN;
			break ;
	}
	mlx_destroy_image(vars->mlx, vars->data->img);
	vars->data->img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->data->addr = mlx_get_data_addr(vars->data->img, &(vars->data->bits_per_pixel),
										 &(vars->data->line_length), &(vars->data->endian));
	flood_fill_screen(vars->data, screen_color);

	mlx_mouse_get_pos(vars->win, &(vars->x), &(vars->y));
	put_lgbt(vars->data, vars->x, vars->y, 200, 100);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);

	return 0;
}

int main()
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "test1");
	vars.data = &img;

	mlx_mouse_hook(vars.win, mouse_hook, &vars);

	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_hook(vars.win, 3, 1L<<1, release_key, &vars);
	mlx_hook(vars.win, 6, 1L<<6, mouse_hook_on_motion, 0);
	mlx_hook(vars.win, 17, 0L, close_win, &vars);


	img.img = mlx_new_image(vars.mlx, 1920, 1080);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);

	flood_fill_screen(&img, SCREEN_BLUE);

//	put_triangle(&img, 500, 500, 200, RED);
//	put_rectangle(&img, 900, 500, 100, 200, BLUE);
//	put_circle(&img, 1200, 400, 100, GREEN);
//	put_lgbt(&img, 10, 500, 500, 250);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	vars.x = 1920 / 2;
	vars.y = 1080 / 2;

	mlx_destroy_image(vars.mlx, (vars.data)->img);
	int x, y;
	t_data nyan;

	nyan.img = mlx_xpm_file_to_image(vars.mlx, "../textures/nyan.xpm", &x, &y);
	nyan.addr = mlx_get_data_addr(nyan.img, &(nyan.bits_per_pixel),
								  &(nyan.line_length), &(nyan.endian));

	mlx_mouse_get_pos(vars.win, &x, &y);
	mlx_put_image_to_window(vars.mlx, vars.win, nyan.img, 500, 500);

	mlx_sync(1);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

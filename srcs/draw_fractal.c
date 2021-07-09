#include "../includes/fractol.h"

static void	put_pixel_mlx(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->address
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	get_color(double r, int i, t_fractal *fractal)
{
	int		color_option;
	double	t;
	double	_t;

	t = (double)i / (double)(fractal->max_iter);
	_t = 1 - t;
	color_option = fractal->color;
	if (color_option == 0)
		return ((int)(COLOR - (i == fractal->max_iter) * COLOR));
	else if (color_option == 1)
		return ((int)(i * COLOR) & 0x00ffffff);
	else if (color_option == 2)
		return (((int)(9 * t * t * 255) & 0xff) << 16
			| ((int)(7 * _t * t * 255) & 0xff) << 8
			| ((int)(3 * _t * _t * 255) & 0xff));
	else if (color_option == 3)
		return ((int)(9 * _t * t * t * t * 255) << 16
			| (int)(15 * _t * _t * t * t * 255) << 8
			| (int)(8.5 * _t * _t * _t * t * 255));
	else
		return (r);
}

static double	get_escape_time(int *i, t_fractal *fractal)
{
	if (fractal->name == MANDELBROT)
	{
		return (mandelbrot(i, fractal));
	}
	else if (fractal->name == JULIA)
	{
		return (julia(i, fractal));
	}
	else if (fractal->name == BURNING_SHIP)
	{
		return (burning_ship(i, fractal));
	}
	else
		return (0.0);
}

void	draw_fractal(t_manager *manager)
{
	int			x;
	int			y;
	int			i;
	double		r;
	t_fractal	*fractal;

	fractal = manager->fractal;
	fractal->scale_re = (fractal->max_re - fractal->min_re) / WIN_WIDTH;
	fractal->scale_im = (fractal->max_im - fractal->min_im) / WIN_HEIGHT;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		fractal->c_im = fractal->max_im - y * fractal->scale_im;
		x = 0;
		while (x < WIN_WIDTH)
		{
			fractal->c_re = fractal->min_re + x * fractal->scale_re;
			r = get_escape_time(&i, fractal);
			put_pixel_mlx(manager->image, x, y, get_color(r, i, fractal));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(manager->mlx,
		manager->window, manager->image->image, 0, 0);
}

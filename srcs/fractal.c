#include "../includes/fractol.h"

void	init_complex(t_complex *this, double re, double im)
{
	this->re = re;
	this->im = im;
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->address + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color(int iteration, t_manager *manager)
{
	// stepwise
//	return ((int)(iteration * 0x00111111) & 0x00ffffff);
	// grayscale

	(void)manager;
	double t = (double)iteration / (double)MAX_ITERATION;
	int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
	int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	int color = red << 16 | green << 8 | blue;
	return (color);
}

void	draw_fractal(t_manager *manager) // FIXME decompose color
{
	int	x;
	int	y;
	int	color;

	init_complex(&(manager->factor),
				 (manager->max.re - manager->min.re) / (WIN_WIDTH - 1),
				 (manager->max.im - manager->min.im) / (WIN_HEIGHT - 1));
	y = 0;
	while (y < WIN_HEIGHT)
	{
		manager->c.im = manager->max.im - y * manager->factor.im;
		x = 0;
		while (x < WIN_WIDTH)
		{
			manager->c.re = manager->min.re + x * manager->factor.re;
			int i = mandelbrot(manager);
//			int i = julia(manager);
			color = get_color(i, manager);
			my_mlx_pixel_put(manager->image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(manager->mlx, manager->window, manager->image->image, 0, 0);
}

int	mandelbrot(t_manager *manager) // FIXME optimization
{
	int			i;
	t_complex	z;

	i = 0;
	init_complex(&z, manager->c.re, manager->c.im);
	while (z.re * z.re + z.im * z.im <= 4 && i < MAX_ITERATION)
	{
		init_complex(&z,
					 z.re * z.re - z.im * z.im + manager->c.re,
					 2.0 * z.re * z.im + manager->c.im);
		i++;
	}
	return (i);
}

int	julia(t_manager *manager)
{
	int			i;
	t_complex	z;

	i = 0;
	init_complex(&z, manager->c.re, manager->c.im);
	while (z.re * z.re + z.im * z.im <= 4 && i < MAX_ITERATION)
	{
		init_complex(&z,
					z.re * z.re - z.im * z.im + manager->k.re,
					2.0 * z.re * z.im + manager->k.im);
		i++;
	}
	return (i);
}

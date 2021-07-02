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
	return ((int)(iteration * 0x00111111) & 0x00ffffff);
	// grayscale

	(void)manager;
//	double t = (double)iteration / (double)MAX_ITERATION;
//	int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
//	int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
//	int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
//	int color = red << 16 | green << 8 | blue;
//	return (color);
}

void	draw_fractal(t_manager *manager) // FIXME decompose color
{
	int	x;
	int	y;
	int	color;

	manager->fractal->scale_re = (manager->fractal->max_re - manager->fractal->min_re) / (WIN_WIDTH - 1); // FIXME make local
	manager->fractal->scale_im = (manager->fractal->max_im - manager->fractal->min_im) / (WIN_HEIGHT - 1);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		manager->fractal->c_im = manager->fractal->max_im - y * manager->fractal->scale_im;
		x = 0;
		while (x < WIN_WIDTH)
		{
			manager->fractal->c_re = manager->fractal->min_re + x * manager->fractal->scale_re;
//			int i = mandelbrot(manager);
			int i = julia(manager);
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
	int		i;
	double	z_re;
	double	z_im;
	double	z_re_2;
	double	z_im_2;

	i = 0;
	z_re = manager->fractal->c_re;
	z_im = manager->fractal->c_im;
	z_re_2 = z_re * z_re;
	z_im_2 = z_im * z_im;
	while (z_re_2 + z_im_2 <= 4 && i < MAX_ITERATION)
	{
		z_im = (z_re + z_re) * z_im + manager->fractal->c_im;
		z_re = z_re_2 - z_im_2 + manager->fractal->c_re;
		z_re_2 = z_re * z_re;
		z_im_2 = z_im * z_im;
		i++;
	}
	return (i);
}

int	julia(t_manager *manager)
{
	int		i;
	double	z_re;
	double	z_im;
	double	z_re_2;
	double	z_im_2;

	i = 0;
	z_re = manager->fractal->c_re;
	z_im = manager->fractal->c_im;
	z_re_2 = z_re * z_re;
	z_im_2 = z_im * z_im;
	while (z_re_2 + z_im_2 <= 4 && i < MAX_ITERATION)
	{
		z_im = 2 * z_re * z_im + manager->fractal->k_re;
		z_re = z_re_2 - z_im_2 + manager->fractal->k_im;
		z_re_2 = z_re * z_re;
		z_im_2 = z_im * z_im;
		i++;
	}
	return (i);
}

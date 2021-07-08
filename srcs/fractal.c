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

int	get_color(double r, int iteration, t_manager *manager)
{
	int	color_option;

	color_option = manager->fractal->color;
	if (color_option == 0) // FIXME
		return ((int)(iteration * 0x00111111) & 0x00ffffff);

	else if (color_option == 1)
	{
		double t = (double)iteration / (double)(manager->fractal->max_iter);
		int red = (int) (9 * (1 - t) * pow(t, 3) * 255);
		int green = (int) (15 * pow((1 - t), 2) * pow(t, 2) * 255);
		int blue = (int) (8.5 * pow((1 - t), 3) * t * 255);
		int color = red << 16 | green << 8 | blue;
		return (color);
	}
	else if (color_option == 2)
	{
		double	log_zn;
		double	nu;

		log_zn = log(r) / 2;
		if (log_zn <= 0)
			log_zn = 1;
		nu = iteration + 1 - log2(log_zn);
		return ((int)(nu * 0x00111111) & 0x00ffffff);
	}
	else // Never reached
		return 1;
}

void	draw_fractal(t_manager *manager) // FIXME decompose color
{
	int	x;
	int	y;
	int	i;
	double	r;
	int	color;

	manager->fractal->scale_re = (manager->fractal->max_re - manager->fractal->min_re) / WIN_WIDTH; // FIXME make local
	manager->fractal->scale_im = (manager->fractal->max_im - manager->fractal->min_im) / WIN_HEIGHT;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		manager->fractal->c_im = manager->fractal->max_im - y * manager->fractal->scale_im;
		x = 0;
		while (x < WIN_WIDTH)
		{
			manager->fractal->c_re = manager->fractal->min_re + x * manager->fractal->scale_re;
			r = mandelbrot(&i, manager);
			color = get_color(r, i, manager);
			my_mlx_pixel_put(manager->image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(manager->mlx, manager->window, manager->image->image, 0, 0);
}

int	does_converge(int *i, double z_re, double z_im, t_manager *manager)
{
	static double	z_re_old;
	static double	z_im_old;
	static int		period;

	if (*i == 0)
	{
		z_re_old = 0;
		z_im_old = 0;
		period = 0;
		return (0);
	}
	if ((fabs(z_re - z_re_old) < EPSILON) && (fabs(z_im - z_im_old) < EPSILON))
	{
		*i = manager->fractal->max_iter;
		return (1);
	}
	period++;
	if (period > 20)
	{
		z_im_old = z_im;
		z_re_old = z_re;
		period = 0;
	}
	return (0);
}

double	mandelbrot(int *i, t_manager *manager) // FIXME optimization
{
	double	z_re;
	double	z_im;
	double	z_re_2;
	double	z_im_2;

	*i = 0;
	z_re = manager->fractal->c_re;
	z_im = manager->fractal->c_im;
	z_re_2 = z_re * z_re;
	z_im_2 = z_im * z_im;
	does_converge(i, z_re, z_im, manager);
	while (z_re_2 + z_im_2 <= 4 && *i < manager->fractal->max_iter
			&& !does_converge(i, z_re, z_im, manager))
	{
		z_im = (z_re + z_re) * z_im + manager->fractal->c_im;
		z_re = z_re_2 - z_im_2 + manager->fractal->c_re;
		z_re_2 = z_re * z_re;
		z_im_2 = z_im * z_im;
		(*i)++;
	}
	return (z_re_2 + z_im_2);
}

double	julia(int *i, t_manager *manager)
{
	double	z_re;
	double	z_im;
	double	z_re_2;
	double	z_im_2;

	*i = 0;
	z_re = manager->fractal->c_re;
	z_im = manager->fractal->c_im;
	z_re_2 = z_re * z_re;
	z_im_2 = z_im * z_im;
	does_converge(i, z_re, z_im, manager);
	while (z_re_2 + z_im_2 <= 4 && *i < manager->fractal->max_iter
			&& !does_converge(i, z_re, z_im, manager))
	{
		z_im = (z_re + z_re) * z_im + manager->fractal->k_re;
		z_re = z_re_2 - z_im_2 + manager->fractal->k_im;
		z_re_2 = z_re * z_re;
		z_im_2 = z_im * z_im;
		(*i)++;
	}
	return (z_re_2 + z_im_2);
}

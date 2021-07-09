#include "../includes/fractol.h"

static int	does_converge(int *i, double z_re, double z_im, t_fractal *fractal)
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
		*i = fractal->max_iter;
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

double	mandelbrot(int *i, t_fractal *fractal)
{
	double	z_re;
	double	z_im;
	double	z_re_2;
	double	z_im_2;

	*i = 0;
	z_re = fractal->c_re;
	z_im = fractal->c_im;
	z_re_2 = z_re * z_re;
	z_im_2 = z_im * z_im;
	does_converge(i, z_re, z_im, fractal);
	while (z_re_2 + z_im_2 <= 4 && *i < fractal->max_iter
		   && !does_converge(i, z_re, z_im, fractal))
	{
		z_im = (z_re + z_re) * z_im + fractal->c_im;
		z_re = z_re_2 - z_im_2 + fractal->c_re;
		z_re_2 = z_re * z_re;
		z_im_2 = z_im * z_im;
		(*i)++;
	}
	return (z_re_2 + z_im_2);
}

double	julia(int *i, t_fractal *fractal)
{
	double	z_re;
	double	z_im;
	double	z_re_2;
	double	z_im_2;

	*i = 0;
	z_re = fractal->c_re;
	z_im = fractal->c_im;
	z_re_2 = z_re * z_re;
	z_im_2 = z_im * z_im;
	does_converge(i, z_re, z_im, fractal);
	while (z_re_2 + z_im_2 <= 4 && *i < fractal->max_iter
		   && !does_converge(i, z_re, z_im, fractal))
	{
		z_im = (z_re + z_re) * z_im + fractal->k_im;
		z_re = z_re_2 - z_im_2 + fractal->k_re;
		z_re_2 = z_re * z_re;
		z_im_2 = z_im * z_im;
		(*i)++;
	}
	return (z_re_2 + z_im_2);
}

double	burning_ship(int *i, t_fractal *fractal)
{
	double	z_re;
	double	z_im;
	double	z_re_2;
	double	z_im_2;

	*i = 0;
	z_re = fractal->c_re;
	z_im = fractal->c_im;
	z_re_2 = z_re * z_re;
	z_im_2 = z_im * z_im;
	does_converge(i, z_re, z_im, fractal);
	while (z_re_2 + z_im_2 <= 4 && *i < fractal->max_iter
		   && !does_converge(i, z_re, z_im, fractal))
	{
		z_im = fabs((z_re + z_re) * z_im) - fractal->c_im;
		z_re = z_re_2 - z_im_2 - fractal->c_re;
		z_re_2 = z_re * z_re;
		z_im_2 = z_im * z_im;
		(*i)++;
	}
	return (z_re_2 + z_im_2);
}

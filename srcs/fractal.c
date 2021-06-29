#include "../includes/fractol.h"

void	complex_init(t_complex *this, double re, double im)
{
	this->re = re;
	this->im = im;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mandelbrot(t_data *data)
{
	t_complex	min, max;
	complex_init(&min, -2.0, -2.0);
	complex_init(&max, 2.0, min.im + (max.re - min.re) * WIN_HEIGHT / WIN_WIDTH); // FIXME
//	complex_init(&min, -2.0, -2.0);
//	complex_init(&max, 2.0, 2.0); // FIXME

	t_complex	factor;
	complex_init(&factor,
				 (max.re - min.re) / (WIN_WIDTH - 1),
				 (max.im - min.im) / (WIN_HEIGHT - 1)
				 );
	t_complex	c;
	int y = 0;
	while (y < WIN_HEIGHT)
	{
		c.im = max.im - y * factor.im;
		int x = 0;
		while (x < WIN_WIDTH)
		{
			c.re = min.re + x * factor.re;
			t_complex z;
			complex_init(&z, c.re, c.im);
			int i = 0;
			while (z.re * z.re + z.im * z.im <= 4 && i < MAX_ITERATION)
			{
				complex_init(&z, z.re * z.re - z.im * z.im + c.re, 2 * z.re * z.im + c.im);
				i++;
			}
			double t = (double)i / (double)MAX_ITERATION;
			int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
			int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
			int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
			int color = red << 16 | green << 8 | blue;
//			if (i == MAX_ITERATION)
//				color = 0x00FF0018;
//			else
//				color = 0x001800FF;
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	julia(t_data *data)
{
	t_complex	min, max;
	complex_init(&min, -2.0, -2.0);
	complex_init(&max, 2.0, min.im + (max.re - min.re) * WIN_HEIGHT / WIN_WIDTH); // FIXME

	t_complex	factor;
	complex_init(&factor,
				 (max.re - min.re) / (WIN_WIDTH - 1),
				 (max.im - min.im) / (WIN_HEIGHT - 1)
	);
	t_complex	k;
	int y = 0;
	while (y < WIN_HEIGHT)
	{
		k.im = 0.6;
		int x = 0;
		while (x < WIN_WIDTH)
		{
			k.re = -0.4;
			t_complex z;
			complex_init(&z, k.re, k.im);
			int i = 0;
			while (z.re * z.re + z.im * z.im <= 4 && i < MAX_ITERATION)
			{
				complex_init(&z, z.re * z.re - z.im * z.im + k.re, 2 * z.re * z.im + k.im);
				i++;
			}
			double t = (double)i / (double)MAX_ITERATION;
			int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
			int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
			int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
			int color = red << 16 | green << 8 | blue;
//			if (i == MAX_ITERATION)
//				color = 0x00FF0018;
//			else
//				color = 0x001800FF;
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

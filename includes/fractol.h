#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"

# define WIN_HEIGHT		1080
# define WIN_WIDTH		1920
# define MAX_ITERATION	100
# define EPSILON		0.000001

# define MANDELBROT		0
# define JULIA			1
# define BURNING_SHIP	2
# define COLOR			0xffcccc

# define MIN_RE			-2.0
# define MIN_IM			-2.0
# define MAX_RE			2.0

typedef struct s_image
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_fractal
{
	int			name;
	double		min_re;
	double		min_im;
	double		max_re;
	double		max_im;
	double		scale_re;
	double		scale_im;
	double		c_re;
	double		c_im;
	double		k_re;
	double		k_im;
	int			max_iter;
	int			color;
}	t_fractal;

typedef struct s_manager
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_fractal	*fractal;
}	t_manager;

double		mandelbrot(int *i, t_fractal *fractal);
double		julia(int *i, t_fractal *fractal);
double		burning_ship(int *i, t_fractal *fractal);

void		draw_fractal(t_manager *manager);
t_manager	*init_manager(int argc, char *argv[]);

#endif

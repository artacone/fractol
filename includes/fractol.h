#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../mlx/mlx.h"

#define WIN_HEIGHT	1080
#define WIN_WIDTH	1920
#define MAX_ITERATION	50

typedef struct s_complex {
	double	re;
	double	im;
}	t_complex;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*data;
	int		x;
	int		y;
}	t_vars;

void	mandelbrot(t_data *data);
void	julia(t_data *data);

#endif

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../mlx/mlx.h"

#define WIN_HEIGHT			1080
#define WIN_WIDTH			1920
#define MAX_ITERATION		250

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5
# define KEY_ESC			53

# define EVENT_KEY_PRESS						2
# define EVENT_KEY_RELEASE						3
# define EVENT_BUTTON_PRESS						4
# define EVENT_BUTTON_RELEASE					5
# define EVENT_MOTION_NOTIFY					6
# define EVENT_EXPOSE							12
# define EVENT_DESTROY							17

# define MASK_KEY_PRESS							1L << 0U
# define MASK_KEY_RELEASE						1L << 1U
# define MASK_BUTTON_PRESS						1L << 2U
# define MASK_BUTTON_RELEASE					1L << 3U
# define MASK_POINTER_MOTION					1L << 6U
# define MASK_EXPOSE							1L << 15U
# define MASK_DESTROY							1L << 17U

# define ERROR_ALLOC		1
# define ERROR_MLX_INIT		-1
# define ERROR_WIN_INIT		-2
# define ERROR_IMG_ADDR		-3

typedef struct s_complex {
	double	re;
	double	im;
}	t_complex;

typedef struct s_image
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

// TODO Add options
typedef struct s_fractal
{
	char		*name;
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
}	t_fractal;

typedef struct s_manager
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_fractal	*fractal;
}	t_manager;



int		mandelbrot(t_manager *manager);
int		julia(t_manager *manager);
void	init_complex(t_complex *this, double re, double im);
void	draw_fractal(t_manager *manager);


int	key_hook(int keycode, t_manager *manager);
int	close_win(int keycode, t_manager *manager);
int	zoom(int button, int x, int y, t_manager *manager);

void	handle_error(int error_code);

#endif

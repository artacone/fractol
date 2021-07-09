#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "../mlx/mlx.h"
#include "../libft/includes/libft.h"

#define COLOR			0xffcccc
#define WIN_HEIGHT		1080
#define WIN_WIDTH		1920
#define MAX_ITERATION	100
#define EPSILON			0.000001
#define ZOOM_IN_SCALE	1.20
#define ZOOM_OUT_SCALE	0.80
#define SHIFT_SCALE		0.10

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define KEY_ESC			53
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_F				3
# define KEY_Q				12
# define KEY_W				13
# define KEY_E				14
# define KEY_C				8

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
# define ERROR_USAGE		-4


# define MANDELBROT		0
# define JULIA			1
# define BURNING_SHIP	2


# define MIN_RE			-2.0
# define MIN_IM			-2.0
# define MAX_RE			2.0
# define MAX_IM			(MIN_IM + (MAX_RE - MIN_RE) * WIN_HEIGHT / WIN_WIDTH)

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



double	mandelbrot(int *i, t_fractal *fractal);
double	julia(int *i, t_fractal *fractal);
double	burning_ship(int *i, t_fractal *fractal);
void	draw_fractal(t_manager *manager);

t_manager	*init_manager(int argc, char *argv[]);


int	key_hook(int keycode, t_manager *manager);
int	close_win(int keycode, t_manager *manager);
int	mouse_button(int button, int x, int y, t_manager *manager);

void	handle_error(int error_code);

#endif

#include "../includes/fractol.h"

static t_image	*init_image(void *mlx)
{
	t_image	*image;

	image = (t_image *)malloc(sizeof(t_image));
	if (image == NULL)
		handle_error(ERROR_ALLOC);
	image->image = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	image->address = mlx_get_data_addr(image->image, &(image->bits_per_pixel),
			   &(image->line_length), &(image->endian));
	if (image->address == NULL)
		handle_error(ERROR_IMG_ADDR);
	return (image);
}

static double	ft_atof(char *str)
{
	double	f_int;
	double	f_frac;
	double	sign;
	char	*str_frac;

	f_int = ft_atoi(str);
	if (f_int >= 0)
		sign = 1;
	else
	{
		sign = -1;
		f_int = 0 - f_int;
	}
	str_frac = ft_strchr(str, '.');
	if (str_frac++ != NULL)
		f_frac = ft_atoi(str_frac) / pow(10, ft_strlen(str_frac));
	else
		f_frac = 0.0;
	return (sign * (f_int + f_frac));
}

static void	select_fractal(t_fractal *fractal, int argc, char *argv[])
{
	if (ft_strcmp(argv[1], "julia") == 0)
	{
		fractal->name = JULIA;
		if (argc == 2)
		{
			fractal->k_re = -0.4;
			fractal->k_im = 0.6;
		}
		else if (argc == 4)
		{
			fractal->k_re = ft_atof(argv[2]);
			fractal->k_im = ft_atof(argv[3]);
		}
		else
			handle_error(ERROR_USAGE);
	}
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		fractal->name = MANDELBROT;
	else if (ft_strcmp(argv[1], "burning_ship") == 0)
		fractal->name = BURNING_SHIP;
	else
		handle_error(ERROR_USAGE);
}

static t_fractal	*init_fractal(int argc, char *argv[])
{
	t_fractal	*fractal;

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (fractal == NULL)
		handle_error(ERROR_ALLOC);
	select_fractal(fractal, argc, argv);
	fractal->min_re = MIN_RE;
	fractal->min_im = MIN_IM;
	fractal->max_re = MAX_RE;
	fractal->max_im = MAX_IM;
	fractal->max_iter = MAX_ITERATION;
	fractal->color = 0;
	return (fractal);
}

t_manager	*init_manager(int argc, char *argv[])
{
	t_manager	*manager;

	manager = (t_manager *)malloc(sizeof(t_manager));
	if (manager == NULL)
		handle_error(ERROR_ALLOC);
	manager->mlx = mlx_init();
	if (manager->mlx == NULL)
		handle_error(ERROR_MLX_INIT);
	manager->window = mlx_new_window(manager->mlx,
			 WIN_WIDTH, WIN_HEIGHT, "fract-ol");
	if (manager->window == NULL)
		handle_error(ERROR_WIN_INIT);
	manager->image = init_image(manager->mlx);
	manager->fractal = init_fractal(argc, argv);
	mlx_hook(manager->window,
		 EVENT_KEY_PRESS, MASK_KEY_PRESS, key_hook, manager);
	mlx_hook(manager->window,
		 EVENT_DESTROY, MASK_DESTROY, close_win, manager);
	mlx_hook(manager->window,
		 EVENT_BUTTON_PRESS, MASK_BUTTON_PRESS, mouse_button, manager);
	return (manager);
}

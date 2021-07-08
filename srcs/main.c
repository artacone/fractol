#include "../includes/fractol.h"

/*
 * TODO
 * main arguments
 * handle usage error
 * help menu
 * optimization
 * more colorings
 * more fractals
 */

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

static t_fractal	*init_fractal(void) // TODO different fractals; add defines
{
	t_fractal	*fractal;

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (fractal == NULL)
		handle_error(ERROR_ALLOC);
	fractal->name = "mandelbrot"; // FIXME
	fractal->min_re = -2.0;
	fractal->min_im = -2.0;
	fractal->max_re = 2.0;
	fractal->max_im = fractal->min_im + (fractal->max_re - fractal->min_re) * WIN_HEIGHT / WIN_WIDTH;
	fractal->k_re = -0.4;
	fractal->k_im = 0.6;
	fractal->max_iter = MAX_ITERATION;
	fractal->color = 0;
	return (fractal);
}

static t_manager	*init_manager()
{
	t_manager	*manager;

	manager = (t_manager *)malloc(sizeof(t_manager));
	if (manager == NULL)
		handle_error(ERROR_ALLOC);
	manager->mlx = mlx_init();
	if (manager->mlx == NULL)
		handle_error(ERROR_MLX_INIT);
	manager->window = mlx_new_window(manager->mlx, WIN_WIDTH, WIN_HEIGHT, "fract-ol");
	if (manager->window == NULL)
		handle_error(ERROR_WIN_INIT);
	manager->image = init_image(manager->mlx);
	manager->fractal = init_fractal();

	mlx_hook(manager->window, EVENT_KEY_PRESS, MASK_KEY_PRESS, key_hook, manager);
	mlx_hook(manager->window, EVENT_DESTROY, MASK_DESTROY, close_win, manager);
	mlx_hook(manager->window, EVENT_BUTTON_PRESS, MASK_BUTTON_PRESS, mouse_button, manager);
	return (manager);
}

int main(int argc, char *argv[])
{
	t_manager	*manager;

	manager = init_manager();

	draw_fractal(manager);

	mlx_loop(manager->mlx);
	(void)argc;
	(void)argv;
	return (0);
}

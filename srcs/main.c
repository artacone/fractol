#include "../includes/fractol.h"

/*
 * TODO
 * main arguments
 * handle usage error
 * help menu
 * optimization
 * moving with arrows
 * more fractals
 */
static t_image	*init_image(void *mlx) // FIXME error handle
{
	t_image	*image;

	image = (t_image *)malloc(sizeof(t_image));
	image->image = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	image->address = mlx_get_data_addr(image->image, &(image->bits_per_pixel),
									   &(image->line_length), &(image->endian));
	return (image);
}

static t_manager	*init_manager() // FIXME error handle
{
	t_manager	*manager;

	manager = (t_manager *)malloc(sizeof(t_manager));
	manager->mlx = mlx_init();
	manager->window = mlx_new_window(manager->mlx, WIN_WIDTH, WIN_HEIGHT, "fract-ol");
	manager->image = init_image(manager->mlx);

	init_complex(&(manager->min), -2.0, -2.0);
	manager->max.re = 2.0;
	manager->max.im = manager->min.im + (manager->max.re - manager->min.re) * WIN_HEIGHT / WIN_WIDTH;

	init_complex(&(manager->k),-0.4, 0.6);


	mlx_hook(manager->window, EVENT_KEY_PRESS, MASK_KEY_PRESS, key_hook, manager);
	mlx_hook(manager->window, EVENT_DESTROY, MASK_DESTROY, close_win, manager);
	mlx_hook(manager->window, EVENT_BUTTON_PRESS, MASK_BUTTON_PRESS, zoom, manager);
	return (manager);
}

int main()
{
	t_manager	*manager;

	manager = init_manager();

	draw_fractal(manager);

	mlx_loop(manager->mlx);
	return (0);
}

#include "../includes/fractol.h"

/*
 * TODO
 * help menu
 */

int	main(int argc, char *argv[])
{
	t_manager	*manager;

	if (argc < 2)
		handle_error(ERROR_USAGE);
	manager = init_manager(argc, argv);
	draw_fractal(manager);
	mlx_loop(manager->mlx);
	return (0);
}

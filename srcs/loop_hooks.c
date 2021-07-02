#include "../includes/fractol.h"

int	key_hook(int keycode, t_manager *manager)
{
	if (keycode == KEY_ESC)
	{
		printf("ESC pressed! Goodbye!\n");
		exit(0);
		(void)manager;
	}
	return (keycode);
}

int	close_win(int keycode, t_manager *manager)
{
	printf("Farewell, friend!\n\n");
	exit(0);
	(void)manager;
	return (keycode);
}

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int	zoom(int button, int x, int y, t_manager *manager)
{
	double	mouse_x;
	double	mouse_y;
	double	interpolation;
	double	zoom;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mouse_x = (double)x / (WIN_WIDTH / (manager->fractal->max_re - manager->fractal->min_re)) + manager->fractal->min_re;
		mouse_y = (double)y / (WIN_HEIGHT / (manager->fractal->max_im - manager->fractal->min_im)) * (-1) + manager->fractal->max_im;
		if (button == MOUSE_SCROLL_UP)
			zoom = 0.80;
		else
			zoom = 1.20;
		interpolation = 1.0 / zoom;
		manager->fractal->min_re = interpolate(mouse_x, manager->fractal->min_re, interpolation);
		manager->fractal->min_im = interpolate(mouse_y, manager->fractal->min_im, interpolation);
		manager->fractal->max_re = interpolate(mouse_x, manager->fractal->max_re, interpolation);
		manager->fractal->max_im = interpolate(mouse_y, manager->fractal->max_im, interpolation);
		draw_fractal(manager);
	}
	return (0);
}
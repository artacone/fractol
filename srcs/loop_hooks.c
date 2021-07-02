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
	t_complex	mouse;
	double		interpolation;
	double		zoom;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		printf("Zooming...1\n");
		init_complex(&mouse,
					 (double)x / (WIN_WIDTH / (manager->max.re - manager->min.re)) + manager->min.re,
					 (double)y / (WIN_HEIGHT / (manager->max.im - manager->min.im)) * (-1) + manager->max.im);

		printf("Zooming...\n");
		if (button == MOUSE_SCROLL_UP)
			zoom = 0.80;
		else
			zoom = 1.20;
		interpolation = 1.0 / zoom;
		manager->min.re = interpolate(mouse.re, manager->min.re, interpolation);
		manager->min.im = interpolate(mouse.im, manager->min.im, interpolation);
		manager->max.re = interpolate(mouse.re, manager->max.re, interpolation);
		manager->max.im = interpolate(mouse.im, manager->max.im, interpolation);
		draw_fractal(manager);
	}
	return (0);
}
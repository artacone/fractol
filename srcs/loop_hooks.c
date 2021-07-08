#include "../includes/fractol.h"

int	close_win(int keycode, t_manager *manager)
{
	printf("Farewell, friend!\n\n");
	exit(0);
	(void)manager;
	return (keycode);
}

static void	change_max_iter(int keycode, t_manager *manager)
{
	if (keycode == KEY_Q)
	{
		manager->fractal->max_iter = (int)(manager->fractal->max_iter * 0.95);
	}
	else
	{
		manager->fractal->max_iter = (int)(manager->fractal->max_iter * 1.05);
	}
}

static void	move_plane(int keycode, t_manager *manager)
{
	double	shift;

	shift = (manager->fractal->max_re - manager->fractal->min_re) * 0.05;
	if (keycode == KEY_A)
	{
		manager->fractal->min_re -= shift;
		manager->fractal->max_re -= shift;
	}
	else if (keycode == KEY_D)
	{
		manager->fractal->min_re += shift;
		manager->fractal->max_re += shift;
	}
	else if (keycode == KEY_W)
	{
		manager->fractal->min_im += shift;
		manager->fractal->max_im += shift;
	}
	else
	{
		manager->fractal->min_im -= shift;
		manager->fractal->max_im -= shift;
	}
}

int	key_hook(int keycode, t_manager *manager)
{
	if (keycode == KEY_ESC)
		close_win(keycode, manager);
	else if (keycode == KEY_Q || keycode == KEY_E)
		change_max_iter(keycode, manager);
	else if (keycode == KEY_A || keycode == KEY_S
			|| keycode == KEY_D || keycode == KEY_W)
		move_plane(keycode, manager);
	else if (keycode == KEY_C)
	{
		manager->fractal->color += 1;
		manager->fractal->color %= 2;
	}
	draw_fractal(manager);
	return (keycode);
}

static void	zoom(t_fractal *fractal, double x, double y, double zoom_scale)
{
	double	mouse_x;
	double	mouse_y;

	mouse_x = fractal->min_re + x * fractal->scale_re;
	mouse_y = fractal->max_im - y * fractal->scale_im;
	fractal->min_re = mouse_x + (fractal->min_re - mouse_x) * zoom_scale;
	fractal->min_im = mouse_y + (fractal->min_im - mouse_y) * zoom_scale;
	fractal->max_re = mouse_x + (fractal->max_re - mouse_x) * zoom_scale;
	fractal->max_im = mouse_y + (fractal->max_im - mouse_y) * zoom_scale;
}

int	mouse_button(int button, int x, int y, t_manager *manager)
{
	double	zoom_scale;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		if (button == MOUSE_SCROLL_UP)
			zoom_scale = 1.20;
		else
			zoom_scale = 0.80;
		zoom(manager->fractal, x, y, zoom_scale);
		draw_fractal(manager);
	}
	return (0);
}
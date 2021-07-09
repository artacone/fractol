#include "../includes/fractol.h"

int	close_win(int keycode, t_manager *manager)
{
	printf("Farewell, friend!\n\n");
	exit(0);
	(void)manager;
	return (keycode);
}

static void	move_plane(int keycode, t_fractal *fractal)
{
	double	shift;

	shift = (fractal->max_re - fractal->min_re) * SHIFT_SCALE;
	if (keycode == KEY_A)
	{
		fractal->min_re -= shift;
		fractal->max_re -= shift;
	}
	else if (keycode == KEY_D)
	{
		fractal->min_re += shift;
		fractal->max_re += shift;
	}
	else if (keycode == KEY_W)
	{
		fractal->min_im += shift;
		fractal->max_im += shift;
	}
	else
	{
		fractal->min_im -= shift;
		fractal->max_im -= shift;
	}
}

int	key_hook(int keycode, t_manager *manager)
{
	t_fractal	*fractal;

	fractal = manager->fractal;
	if (keycode == KEY_ESC)
		close_win(keycode, manager);
	else if (keycode == KEY_Q)
		fractal->max_iter = (int)(fractal->max_iter * 0.95);
	else if (keycode == KEY_E)
		fractal->max_iter = (int)(fractal->max_iter * 1.05);
	else if (keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D || keycode == KEY_W)
		move_plane(keycode, fractal);
	else if (keycode == KEY_C)
	{
		fractal->color += 1;
		fractal->color %= 4;
	}
	else
		return (keycode);
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
			zoom_scale = ZOOM_IN_SCALE;
		else
			zoom_scale = ZOOM_OUT_SCALE;
		zoom(manager->fractal, x, y, zoom_scale);
		draw_fractal(manager);
	}
	return (0);
}

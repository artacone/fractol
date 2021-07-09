#include "../includes/fractol.h"

void	handle_error(int error_code)
{
	if (error_code > 0)
	{
		perror(NULL);
	}
	if (error_code == ERROR_USAGE)
	{
		printf("USAGE: ./fractol \"fractal_name\" [\"k_re\" \"k_im\"]\n");
		printf("You can choose \"fractal_name\" from:\n");
		printf("\tmandelbrot\n");
		printf("\tjulia\n");
		printf("\tburning_ship\n");
		printf("When plotting julia you may set initial k_re and k_im, e.g.\n");
		printf("\t-0.79\t0.15\n");
		printf("\t-0.162\t1.04\n");
		printf("\t0.3\t-0.1\n");
		printf("\t-1.476\t0.0\n");
		printf("\t-0.12\t-0.77\n");
		printf("\t0.28\t0.008\n");
	}
	exit(error_code);
}

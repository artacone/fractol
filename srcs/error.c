#include "../includes/fractol.h"

void	handle_error(int error_code)
{
	if (error_code > 0)
	{
		perror(NULL);
	}
	exit(error_code);
}
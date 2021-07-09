#ifndef ERROR_H
# define ERROR_H

# define ERROR_ALLOC		1
# define ERROR_MLX_INIT		-1
# define ERROR_WIN_INIT		-2
# define ERROR_IMG_ADDR		-3
# define ERROR_USAGE		-4

void	handle_error(int error_code);

#endif

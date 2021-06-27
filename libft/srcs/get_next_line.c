#include <libft.h>

static char	*trim_line(char **buf, char **line)
{
	char	*ptr_endl;
	char	*to_free;

	ptr_endl = NULL;
	if (**buf != '\0')
	{
		to_free = *line;
		ptr_endl = ft_strchr(*buf, '\n');
		if (ptr_endl != NULL)
		{
			*ptr_endl = '\0';
			*line = ft_strjoin(*line, *buf);
			ft_strlcpy(*buf, ++ptr_endl, BUFFER_SIZE);
		}
		else
		{
			*line = ft_strjoin(*line, *buf);
			**buf = '\0';
		}
		free(to_free);
	}
	return (ptr_endl);
}

static int	return_handler(char *ptr_endl, char **buf)
{
	if (ptr_endl != NULL)
	{
		return (1);
	}
	else
	{
		free(*buf);
		*buf = NULL;
		return (0);
	}
}

static int	init_handler(int fd, char **line, char **buf)
{
	if (*buf == NULL)
	{
		*buf = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
		if (*buf == NULL)
		{
			return (-1);
		}
	}
	if (BUFFER_SIZE < 1 || line == NULL || read(fd, 0, 0) == -1)
	{
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	*line = ft_calloc(1, 1);
	return (0);
}

static int	error_handler(char **line, ssize_t n_read, char **buf)
{
	if (*line == NULL || n_read == -1)
	{
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*ptr_endl;
	static char	*buf;
	ssize_t		n_read;

	if (init_handler(fd, line, &buf) == -1)
		return (-1);
	if (error_handler(line, 0, &buf) == -1)
		return (-1);
	ptr_endl = trim_line(&buf, line);
	while (ptr_endl == NULL)
	{
		n_read = read(fd, buf, BUFFER_SIZE);
		if (error_handler(line, n_read, &buf) == -1)
			return (-1);
		buf[n_read] = '\0';
		if (n_read == 0)
			break ;
		ptr_endl = trim_line(&buf, line);
	}
	return (return_handler(ptr_endl, &buf));
}

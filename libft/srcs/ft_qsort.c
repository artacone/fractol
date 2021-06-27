static void	ft_swap(int *l, int *r)
{
	int	tmp;

	tmp = *l;
	*l = *r;
	*r = tmp;
}

static int	qs_partition(int *array, int l, int r)
{
	int	pivot;
	int	less;
	int	i;

	pivot = array[r];
	less = l;
	i = l;
	while (i < r)
	{
		if (array[i] <= pivot)
		{
			ft_swap(array + i, array + less);
			less++;
		}
		i++;
	}
	ft_swap(array + less, array + r);
	return (less);
}

static void	ft_quicksort(int *array, int l, int r)
{
	int	p;

	if (l < r)
	{
		p = qs_partition(array, l, r);
		ft_quicksort(array, l, p - 1);
		ft_quicksort(array, p + 1, r);
	}
}

void	ft_qsort(int *array, int size)
{
	ft_quicksort(array, 0, size - 1);
}

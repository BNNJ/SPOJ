#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
static inline int	test_val(char *tab, int val, int max)
{
	return (tab[max - val / 8] & (1 << val % 8));
}
*/

static void	fill_tab(char *tab, int max)
{
	int	limit = sqrt(max);
	int j, i = 3;

	tab[0] = tab[1] = 0;
	while (i < limit)
	{
		j = i + i;
		while (j <= max)
		{
			tab[j] = 0;
			j += i;
		}
		i += 2;
		while (tab[i] == 0 && i < limit)
			i += 2;
	}
}

static void	print_primes(char *tab, int min, int max)
{
	int	i = min + (~min & 1);

	if (min <= 2)
		printf("2 ");
	while (i <= max)
	{
		if (tab[i] == 1)
			printf("%d ", i);
		i += 2;
	}
	printf("\n");
}

int		main(int argc, const char *argv[])
{
	int		max = atoi(argv[2]);
	int		min = atoi(argv[1]);
	char	*tab;

	if (!(tab = malloc(max)))
	{
		dprintf(2, "malloc error\n");
		return (EXIT_FAILURE);
	}
	memset(tab, 1, max + 1);
	fill_tab(tab, max);
	print_primes(tab, min, max);
	return (EXIT_SUCCESS);
}

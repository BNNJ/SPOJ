#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 1000001

static char	*solve(char *n, int len)
{
	int	i = 0;
	int	j = len - 1;
	int	already_pal = 1;

	while (i < j)
	{
		if (n[i] > n[j])
		{
			n[j] = n[i];
			already_pal = 0;
		}
		else if (n[i] < n[j])
		{
			++n[j - 1];
			n[j] = n[i];
			already_pal = 0;
		}
		++i, --j;
	}
	if (already_pal)
	{
		++n[i];
		n[j] = n[i];
	}
	while (i < len && n[i] > '9')
	{
		n[i] = n[j] = '0';
		++i, --j;
		++n[i], ++n[j];
	}
	if (i == len)
		n[0] = n[len] = '1';
	return (n);
}


/*
** uncomment this line to skip leading zeros
** Don't forget to do the same thing in checker.c
#define SKIP_LEADING_ZERO
*/

#define DEBUG

int			main(void)
{
	int		nb_tests, len, i;
	char	input[BUFF_SIZE];

	fgets(input, BUFF_SIZE, stdin);
	nb_tests = atoi(input);
#ifdef DEBUG
	printf("%d\n", nb_tests);
#endif
	while (--nb_tests >= 0)
	{
		fgets(input, BUFF_SIZE, stdin);
		len = strlen(input) - 1;
		input[len] = 0;
		i = 0;
#ifdef SKIP_LEADING_ZERO
		while (input[i] == '0' && i < len - 1)
			++i;
		len -= i;
#endif
#ifdef DEBUG
		printf("%s\n", input);
#endif
		printf("%s\n", solve(input + i, len));
	}
	return (EXIT_SUCCESS);
}

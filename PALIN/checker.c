#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 1000001

static int	test_pal(char *n, int len)
{
	int	i = 0;
	int	j = len - 1;

	while (i <= j)
	{
		if (n[i] != n[j])
			return (0);
		++i, --j;
	}

	return (1);
}

static int	test_val(char *output, char *input, int out_len, int in_len)
{
	if (out_len != in_len)
		return (out_len > in_len);
	while (*output && *input && *output == *input)
		++output, ++input;
	return (*output > *input);
}

static int	prev_pal(char *n, char *input, int len, int in_len)
{
	int	i = (len - 1) / 2;
	int	j = len / 2;

	--n[i];
	n[j] = n[i];
	while (i >= 0 && n[i] < '0')
	{
		n[i] = n[j] = '9';
		--i, ++j;
		--n[i], -- n[j];
	}
	if (n[0] == '0')
	{
		n[0] = '9';
		--len;
		n[len] = 0;
	}
	if (len > in_len)
		return (0);
	else if (len < in_len)
		return (1);
	while (*n && *n == *input)
		++n, ++input;
	return (*n <= *input);
}

/*
** uncomment this line to skip leading zeros
** Don't forget to do the same thing in palin.c
#define SKIP_LEADING_ZERO
*/

int			main(void)
{
	char	output[BUFF_SIZE];
	char	input[BUFF_SIZE];
	int		out_len, in_len, nb_tests, skip_zero;

	fgets(input, BUFF_SIZE, stdin);
	nb_tests = atoi(input);
	for (int i = 1; i <= nb_tests; ++i)
	{
		printf("-----------\n");
		fgets(input, BUFF_SIZE, stdin);
		in_len = strlen(input) - 1;
		input[in_len] = 0;
		skip_zero = 0;
#ifdef SKIP_LEADING_ZERO
		while (input[skip_zero] == '0' && skip_zero < in_len - 1)
			++skip_zero;
		in_len -= skip_zero;
#endif
		fgets(output, BUFF_SIZE, stdin);
		out_len = strlen(output) - 1;
		output[out_len] = 0;
		if (!test_val(output, input + skip_zero, out_len, in_len))
		{
			printf("ouput isn't bigger than input\n");
			fprintf(stderr, "in: %s\nout: %s\n", input, output);
			return (EXIT_FAILURE);
		}
		if (!test_pal(output, out_len))
		{
			printf("ouput isn't a palindrome\n");
			fprintf(stderr, "in: %s\nout: %s\n", input, output);
			return (EXIT_FAILURE);
		}
		if (!prev_pal(output, input + skip_zero, out_len, in_len))
		{
			printf("smaller valid palindrome found\n");
			fprintf(stderr, "in: %s\nout: %s\n", input, output);
			return (EXIT_FAILURE);
		}
		printf("test %d OK\n", i);
	}
	return (EXIT_SUCCESS);
}

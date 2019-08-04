#include <stdlib.h>		/* malloc */
#include <stdio.h>
#include <string.h>		/* memset memcpy */
#include "arith.h"

#define BUFF_SIZE 1024

/*
** Reverses a string after removing trailing '0's
*/

char 		*str_rev(char *str)
{
	if (!str || ! *str)
		return str;

	int	i = strlen(str) - 1;
	int	j = 0;
	while (i > 0 && str[i] == '0')
	{
		str[i] = 0;
		--i;
	}
	char	ch;
	while (i > j)
	{
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
		--i;
		++j;
	}
	return (str);
}

static int	oplen(char *input)
{
	int		len = 0;

	while (input[len] >= '0' && input[len] <= '9')
		++len;
	return (len);
}

int			get_max_len(int result_len, int len1, int len2)
{
	int	len = len1 > len2 ? len1 : len2 + 1;
	return (len > result_len ? len : result_len);
}

void		print(char *n1, char *n2, char *result, int len1, int len2, char op)
{
	char	line[512];
	int		result_len = strlen(result);
	int		len = get_max_len(result_len, len1, len2);
	int		line_len = result_len > len2 ? result_len : len2 + 1;

	memset(line, '-', line_len);
	line[line_len] = 0;
	printf("%*s\n", len, n1);
	printf("%*c%s\n", len - len2, op, n2);
	printf("%*s\n", len, line);
	printf("%*s\n", len, result);
}

int			main(void)
{
	char	input[BUFF_SIZE];
	char	*output;
	char	n1[512] = {0};
	char	n2[512] = {0};
	int		len1, len2, nb_tests;
	char	op;

	fgets(input, BUFF_SIZE, stdin);
	nb_tests = atoi(input);
	while (--nb_tests >= 0)
	{
		fgets(input, BUFF_SIZE, stdin);
		len1 = oplen(input);
		op = input[len1];
		len2 = oplen(input + len1 + 1);
		memcpy(n1, input, len1);
		n1[len1] = 0;
		memcpy(n2, input + len1 + 1, len2);
		n2[len2] = 0;
		switch (op)
		{
			case '+':
				output = big_add(n1, n2, len1, len2);
				print(n1, n2, output, len1, len2, op);
				break;
			case '-':
				output = big_sub(n1, n2, len1, len2);
				print(n1, n2, output, len1, len2, op);
				break;
			case '*':
				output = big_mul(n1, n2, len1, len2);
				break;
		}
		free(output);
		if (nb_tests > 0)
			printf("\n");
	}
	return (EXIT_SUCCESS);
}

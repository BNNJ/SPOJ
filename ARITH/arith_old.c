#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static int			carry = 0;
static char			output[1024] = {0};

/*
** Utility functions
*/

static void			get_input(char *input, char *n1, char *n2, char *op)
{
	while (*input >= '0' && *input <= '9')
	{
		*n1 = *input;
		++n1, ++input;
	}
	*op = *input++;
	while (*input >= '0' && *input <= '9')
	{
		*n2 = *input;
		++n2, ++input;
	}
}

static int			get_max_len(int len1, int len2)
{
	int	len = len1 > len2 ? len1 : len2 + 1;
	int	output_len = strlen(output);
	return (len > output_len ? len : output_len);
}

/*
** Reverses a string after removing trailing '0's
*/

static char 		*str_rev(char *str)
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

/*
** ADDITION FUNCTIONS
*/

static inline char	simple_add(char a, char b)
{
	char	ret = 0;

	ret = (a - '0') + (b - '0') + carry;
	carry = 0;
	if (ret > 9)
	{
		ret -= 10;
		carry = 1;
	}
	ret += '0';
	return (ret);
}

static void			big_add(char *n1, char *n2, int len1, int len2)
{
	int		i = 0;

	while (--len1 >= 0 && --len2 >= 0)
	{
		output[i] = simple_add(n1[len1], n2[len2]);
		++i;
	}
	if (carry == 1)
		output[i] = '1';
	str_rev(output);
}

/*
** SUBSTRACTION FUNCTIONS
*/

static inline char	simple_sub(char a, char b)
{
	char	ret = 0;

	ret = (a -'0') - (b - '0') - carry;
	carry = 0;
	if (ret < 0)
	{
		ret += 10;
		carry = 1;
	}
	ret += '0';
	return (ret);
}

static void			big_sub(char *n1, char *n2, int len1, int len2)
{
	int		i = 0;

	while (--len1 >= 0 && --len2 >= 0)
	{
		output[i] = simple_sub(n1[len1], n2[len2]);
		++i;
	}
	str_rev(output);
}

/*
** MULTIPLICATION FUNCTIONS
*/

static inline char	simple_mul(char a, char b)
{
	int	result = (a - '0') * (b - '0') + carry;

	carry = result / 10;
	return ((result % 10) + '0');
}

static inline void	medium_mul(char *a, char b, int len, char *result)
{
	int		i = 0;

	while (--len >= 0)
	{
		result[i] = simple_mul(a[len], b);
		++i;
	}
	while (carry > 0)
	{
		result[i] += carry % 10;
		carry /= 10;
		++i;
	}
	carry = 0;
	str_rev(result);
}

static void			sum_mul(char numbers[512][1024], int num)
{
	char	n1[1024];
	char	n2[1024];
	int		len1;
	int		len2;

	for (int i = 0; i < num; i++)
	{
		len1 = strlen(output);
		len2 = strlen(numbers[i]);
		memcpy(n1, output, len1);
		memcpy(n2, numbers[i], len2);
		memset(n2 + len2, '0', i);
		big_add(n1, n2, len1, len2 + i);
		memset(output, 0, sizeof(output));
		printf("#n1: %s\nlen1: %d\n#n2: %s\nlen2: %d\nresult: %s\n",
			n1, len1, n2, len2 + i, output);
	}
}

static void			big_mul(char *n1, char *n2, int len1, int len2)
{
	char	results[512][1024] = {0};
	int		i = 0;

	while (--len2 >= 0)
		medium_mul(n1, n2[len2], len1, results[i++]);
	output[0] = '0';
	sum_mul(results, i);
//	int		big_len = get_max_len(len1, len2);
//	for (int j = 0; j < i; j++)
//		printf("%*s\n", big_len - j, results[j]);
//	printf("@@@ %s @@@\n", output);
}

/*
** main
*/

int					main(void)
{
	char	input[1024] = {0};
	char	op = 0;
	char	n1[512] = {0};
	char	n2[512] = {0};
	char	line[1024];

	memset(line, '-', sizeof(line));
	if (read(1, input, 1024) < 0)
		return (EXIT_FAILURE);
	get_input(input, n1, n2, &op);
	int	len1 = strlen(n1);
	int	len2 = strlen(n2);
	switch (op)
	{
		case '+':
			big_add(n1, n2, len1, len2); break;
		case '-':
			big_sub(n1, n2, len1, len2); break;
		case '*':
			big_mul(n1, n2, len1, len2); break;
	}
	int	len = get_max_len(len1, len2);
	printf("%*s\n%*c%s\n%.*s\n", len, n1, len - len2, op, n2, len, line);
	printf("%*s\n", len1 > len2 ? len1 : len2 + 1, output);
	return (EXIT_SUCCESS);
}

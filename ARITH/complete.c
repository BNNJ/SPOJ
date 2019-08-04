#include <stdlib.h>		/* malloc */
#include <stdio.h>
#include <string.h>		/* memset memcpy */

#define BUFF_SIZE 1024

static int	carry = 0;

/*
** Reverses a string after removing trailing '0's
*/

static char *str_rev(char *str)
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

static int	get_max_len(int result_len, int len1, int len2)
{
	int	len = len1 > len2 ? len1 : len2 + 1;
	return (len > result_len ? len : result_len);
}

static void	print(char *n1, char *n2, char *result, int len1, int len2, char op)
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

static char			*big_add(char *n1, char *n2, int len1, int len2)
{
	char	output[512] = {0};
	int		i = 0;

	--len1, --len2;
	carry = 0;
	while (len1 >= 0 && len2 >= 0)
	{
		output[i] = simple_add(n1[len1], n2[len2]);
		--len1, --len2, ++i;
	}
	while (len1 >= 0)
	{
		output[i] = simple_add(n1[len1], '0');
		--len1, ++i;
	}
	while (len2 >= 0)
	{
		output[i] = simple_add(n2[len2], '0');
		--len2, ++i;
	}
	if (carry == 1)
	output[i] = '1';
	return (strdup(str_rev(output)));
}

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

static char			*big_sub(char *n1, char *n2, int len1, int len2)
{
	char	output[512] = {0};
	int		i = 0;

	--len1, --len2;
	carry = 0;
	while (len1 >= 0 && len2 >= 0)
	{
		output[i] = simple_sub(n1[len1], n2[len2]);
		--len1, --len2, ++i;
	}
	while (len1 >= 0)
	{
		output[i] = simple_sub(n1[len1], '0');
		--len1, ++i;
	}
	while (len2 >= 0)
	{
		output[i] = simple_sub(n2[len2], '0');
		--len2, ++i;
	}
	return(strdup(str_rev(output)));
}

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
		result[i] = (carry % 10) + '0';
		carry /= 10;
		++i;
	}
	carry = 0;
	str_rev(result);
}

static char			*sum_mul(char numbers[512][1024], int num)
{
	char	n1[1024] = {0}, n2[1024] = {0};
	char	*tmp;
	int		len1, len2;

	n1[0] = '0';
	for (int i = 0; i < num; ++i)
	{
		len1 = strlen(n1);
		len2 = strlen(numbers[i]);
		memcpy(n2, numbers[i], len2);
		memset(n2 + len2, '0', i);
		n2[len2 + i] = 0;
		tmp = big_add(n1, n2, len1, len2 + i);
		len1 = strlen(tmp);
		memcpy(n1, tmp, len1);
		n1[len1] = 0;
		free(tmp);
	}
	return (strdup(n1));
}

static void			print_mul(char *n1, char *n2, char *result, int len1, int len2, char results[512][1024])
{
	char	line[1024];
	int		result_len = strlen(result);
	int		len = get_max_len(result_len, len1, len2);
	len1 = strlen(results[0]);
	int		line_len = len1 > len2 ? len1 : len2 + 1;

	memset(line, '-', line_len);
	line[line_len] = 0;
	printf("%*s\n", len, n1);
	printf("%*c%s\n", len - len2, '*', n2);
	printf("%*s\n", len, line);
	for (int j = 0; j < len2; j++)
		printf("%*s\n", len - j, results[j]);
	len2 += strlen(results[len2 - 1]) - 2;
	line_len = result_len > len2 ? result_len : len2 + 1;
	memset(line, '-', line_len);
	line[line_len] = 0;
	printf("%*s\n", len, line);
	printf("%*s\n", len, result);
}

static char			*big_mul(char *n1, char *n2, int len1, int len2)
{
	char	results[512][1024] = {0};
	char	*result;
	int		i = 0;
	int		j = len2;

	carry = 0;
	while (--j >= 0)
		medium_mul(n1, n2[j], len1, results[i++]);
	result = sum_mul(results, len2);
	if (len2 > 1)
		print_mul(n1, n2, result, len1, len2, results);
	else
		print(n1, n2, result, len1, len2, '*');
	return (result);
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
		printf("\n");
	}
	return (EXIT_SUCCESS);
}

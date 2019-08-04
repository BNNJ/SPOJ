#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arith.h"

static int			carry = 0;

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
	len2 = strlen(results[len2 - 1]);
	line_len = result_len > len2 ? result_len : len2 + 1;
	memset(line, '-', line_len);
	line[line_len] = 0;
	printf("%*s\n", len, line);
	printf("%*s\n", len, result);
}

char				*big_mul(char *n1, char *n2, int len1, int len2)
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
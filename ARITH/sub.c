#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arith.h"

static int			carry = 0;

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

char				*big_sub(char *n1, char *n2, int len1, int len2)
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

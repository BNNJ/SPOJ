#include <stdio.h>

static char	carry = 0;
static char leading_zero = 1;

static char	simple_add(char a, char b)
{
	char ret = (a - '0') + (b - '0') + carry;

	if (ret > 9)
	{
		carry = 1;
		ret -= 10;
	}
	else
		carry = 0;
	if (ret == 0 && leading_zero)
		return (0);
	else
		leading_zero = 0;
	return (ret + '0');
}

static char	*addrev(char *a, char *b, char *result)
{
	int		i = 0;
	char	c;

	carry = 0;
	leading_zero = 1;
	while (*a && *b)
	{
		if ((c = simple_add(*a, *b)))
		{
			result[i] = c;
			++i;
		}
		++a;
		++b;
	}
	while (*a)
	{
		if ((c = simple_add(*a, '0')))
		{
			result[i] = c;
			++i;
		}
		++a;
	}
	while (*b)
	{
		if ((c = simple_add(*b, '0')))
		{
			result[i] = c;
			++i;
		}
		++b;
	}
	if (carry)
		result[i++] = '1';
	result[i] = 0;
	return (result);
}

int		main(void)
{
	int		nb_case;
	char	a[16];
	char	b[16];
	char	result[16];

	scanf("%d", &nb_case);
	while (--nb_case >= 0)
	{
		scanf("%s %s", a, b);
		printf("%s\n", addrev(a, b, result));
	}
	return (0);
}

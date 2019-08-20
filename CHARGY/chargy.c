#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	stack[100000];
static int	s_idx = 0;

#define push(x)	stack[s_idx++] = x
#define pop()	stack[--s_idx]
#define peek()	stack[s_idx - 1]

int		main(void)
{
	int		n;
	char	charge = 0;

	scanf("%d", &n);
	while (--n >= 0)
	{
		scanf("%hhd", &charge);
		if (s_idx == 0 || peek() == 0 || charge == 0 || peek() == charge)
			push(charge);
		else
			charge = pop();
	}
	printf("%d\n", s_idx);
	return (EXIT_SUCCESS);
}

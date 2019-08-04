#include <stdio.h>
//#include <stdlib.h>

int		main(void)
{
	int	val;

	while (scanf("%d", &val) > 0 && val != 42)
		printf("%d\n", val);
	return (0);
}
/*
int		main(void)
{
	char	val[3];

	while (fgets(val, sizeof(val), stdin))
	{
		if (val[0] == '4' && val[1] == '2')
			break;
		printf("%s", val);
	}
	return (0);
}
*/

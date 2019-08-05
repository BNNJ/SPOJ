#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 1000000001

int		main(int argc, char **argv)
{
	int		len, nb_tests;
	char	buffer[BUFF_SIZE];

	if (argc == 2)
	{
		nb_tests = atoi(argv[1]);
		printf("%d\n", nb_tests);
		srand(time(NULL));
		while (--nb_tests >= 0)
		{
			len = rand() % BUFF_SIZE;
			for (int i = 0; i < len; ++i)
				buffer[i] = rand() % 10 + '0';
			buffer[len] = 0;
			printf("%s\n", buffer);
		}
	}
	return (EXIT_SUCCESS);
}
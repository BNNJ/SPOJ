#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define	MIN_NODES	5
#define	MAX_NODES	20
#define	MIN_EDGES	1
#define	MAX_EDGES	(MAX_NODES / 2)
#define	MIN_PATHS	1	
#define	MAX_PATHS	(MAX_NODES / 4)
#define	MIN_NAME	3
#define	MAX_NAME	10
#define	MIN_COST	1
#define	MAX_COST	100

#define RNG(x, y)	rand() % (x - y) + y

int		already_exists(int n, int *edges, int nb_edges)
{
	for (int i = 0; i < nb_edges; ++i)
		if (n == edges[i])
			return (1);
	return (0);
}

void	gen_edges(int n, int nb_edges, int nb_nodes)
{
	int	edges[nb_edges + 1];
	int	created = 0;

	edges[0] = n;
	while (++created < nb_edges)
	{
		while (already_exists((n = RNG(MAX_NODES, 1)), edges, created))
			printf("n = %d, nb_nodes = %d, nb_edges = %d, created = %d\n",
				n, nb_nodes, nb_edges, created);
		printf("%d %d\n", n, RNG(MAX_COST, MIN_COST));
		edges[created++] = n;
	}
}

char	*gen_node(int n, int nb_nodes)
{
	int		nb_edges = RNG(MAX_EDGES, MIN_EDGES);
	int		name_len = RNG(MAX_NAME, MIN_NAME);
	char	*name;

	name = malloc(name_len);
	for (int i = 0; i < name_len; ++i)
		name[i] = rand() % 26 + 'a';
	name[name_len] = 0;
	printf("%s\n", name);
	printf("%d\n", nb_edges);
	gen_edges(n, nb_edges, nb_nodes);
	return (name);
}

void	gen_start_end(char **names, int nb_nodes)
{
	int		nb_paths = RNG(MAX_PATHS, MIN_PATHS);
	int		start, end;

	printf("%d\n", nb_paths);
	while (--nb_paths >= 0)
	{
		start = rand() % nb_nodes;
		while ((end = rand() % nb_nodes) == start);
		printf("%s %s\n", names[start], names[end]);
	}
}

void	gen_graph()
{
	int		nb_nodes = RNG(MAX_NODES, MIN_NODES);

	char	**names;
	printf("%d\n", nb_nodes);
	names = malloc(sizeof(char*) * nb_nodes);
	for (int i = 0; i <= nb_nodes; ++i)
		names[i] = gen_node(i + 1, nb_nodes);
	gen_start_end(names, nb_nodes);
}

int		main(int argc, char **argv)
{
	int	nb_tests;

	if (argc == 2)
	{
		nb_tests = atoi(argv[1]);
		printf("%d\n", nb_tests);
		srand(time(NULL));
		while (--nb_tests >= 0)
		{
			gen_graph();
			printf("\n");
		}
	}
	return (EXIT_SUCCESS);
}
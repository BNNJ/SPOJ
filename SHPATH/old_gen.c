#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define	MIN_NODES	5
#define	MAX_NODES	20
#define	MIN_EDGES	1
#define	MAX_EDGES	(MAX_NODES * 2)
#define	MIN_PATHS	1	
#define	MAX_PATHS	(MAX_NODES / 4)
#define	MIN_NAME	3
#define	MAX_NAME	10
#define	MIN_COST	1
#define	MAX_COST	100

#define RNG(x, y)	rand() % (x - y) + y


void		print_matrix(int **m, int size)
{
	printf("----- MATRIX -----\nsize: %d\n", size);
	printf("   0");
	for (int i = 0; i < size; ++i)
		printf("%4d", i + 1);
	printf("\n");
	for (int i = 0; i < size; ++i)
	{
		printf("%4d", i + 1);
		for (int j = 0; j < size; ++j)
			printf("%4d", m[i][j]);
		printf("\n");
	}
}


int		**gen_edges(int nb_nodes)
{
	int	**edges;
	int	nb_edges = RNG(nb_nodes * 2, nb_nodes);
	int	j, k, cost;

	edges = malloc(sizeof(int*) * nb_nodes);
	for (int i = 0; i < nb_nodes; ++i)
		edges[i] = calloc(sizeof(int), nb_nodes);
	for (int i = 0; i < nb_edges; ++i)
	{
		do
		{
			j = RNG(nb_nodes, 0);
			k = RNG(nb_nodes, 0);
		}
		while (edges[j][k] != 0 || j == k);
		cost = RNG(MAX_COST, MIN_COST);
		edges[j][k] = cost;
		edges[k][j] = cost;
	}
	return (edges);
}

char	*gen_node(int n, int nb_nodes, int **edges)
{
	int		nb_edges = 0;
	int		name_len = RNG(MAX_NAME, MIN_NAME);
	char	*name;

	name = malloc(name_len);
	for (int i = 0; i < name_len; ++i)
		name[i] = rand() % 26 + 'a';
	name[name_len] = 0;
	printf("%s\n", name);
	for (int i = 0; i < nb_nodes; ++i)
		nb_edges += (edges[n][i] != 0);
	printf("%d\n", nb_edges);
	for (int i = 0; i < nb_nodes; ++i)
		if (edges[n][i] != 0)
			printf("%d %d\n", i + 1, edges[n][i]);
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
	int		**edges;

	char	**names;
	printf("%d\n", nb_nodes);
	edges = gen_edges(nb_nodes);
//	print_matrix(edges, nb_nodes);
	names = malloc(sizeof(char*) * nb_nodes);
	for (int i = 0; i < nb_nodes; ++i)
		names[i] = gen_node(i, nb_nodes, edges);
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
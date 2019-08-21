#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define	MIN_NODES	5
#define	MAX_NODES	20
#define	MIN_EDGES	1
#define	MAX_EDGES	(MAX_NODES * 2)
#define	MIN_REQ		1	
#define	MAX_REQ		(MAX_NODES / 4)
#define	MIN_NAME	3
#define	MAX_NAME	10
#define	MIN_COST	1
#define	MAX_COST	100
#define	MAX_POP		3

#define RNG(x, y)	rand() % (x - y) + y

typedef struct	s_graph
{
	char	**nodes;
	int		**edges;
	int		nb_nodes;
}				t_graph;

/*********************************** DEBUG ************************************/

/*
** uncomment the define to print some debug informations
*/

// #define DEBUG

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

/****************************** GRAPH GENERATOR *******************************/

char	*gen_name(void)
{
	char	*name;
	int		len = RNG(MAX_NAME, MIN_NAME);

	name = malloc(len + 1);
	for (int i = 0; i < len; ++i)
		name[i] = RNG('z', 'a');
	name[len] = 0;
	return (name);
}

char	**gen_nodes(int nb_nodes)
{
	char	**nodes;

	nodes = malloc(sizeof(char*) * nb_nodes);
	for (int i = 0; i < nb_nodes; ++i)
		nodes[i] = gen_name();
	return (nodes);
}

/*
** Generates a symmetrical matrix of size nb_nodes and fills it with the costs
** associated with each edge.
** It is filled line by line, starting from row line + 1,
** so only the top right half is computed. The other half is filled by symmetry.
** like this (the processed cells are marked with an x):
** 0 1 2 3 4
** 1 - x x x
** 2 - - x x
** 3 - - - x
** 4 - - - -
** For each processed cell, a random number between 0 and MAX_POP is generated,
** and if this number is 0 then a cost is generated and stored in this cell.
*/

int		**gen_edges(int nb_nodes)
{
	int	**edges;

	edges = malloc(sizeof(int*) * nb_nodes);
	for (int i = 0; i < nb_nodes; ++i)
		edges[i] = calloc(sizeof(int), nb_nodes);
	for (int i = 0; i < nb_nodes; ++i)
		for (int j = i + 1; j < nb_nodes; ++j)
			edges[i][j] = edges[j][i] = RNG(MAX_POP, 0) == 0 ? RNG(MAX_COST, MIN_COST) : 0;
	return (edges);
}

void	gen_graph(t_graph *g)
{
	g->nb_nodes = RNG(MAX_NODES, MIN_NODES);
	g->nodes = gen_nodes(g->nb_nodes);
	g->edges = gen_edges(g->nb_nodes);
}

/****************************** OUTPUT DISPLAY ********************************/

void	print_node(t_graph *g, int node)
{
	int	nb_edges = 0;

	for (int i = 0; i < g->nb_nodes; ++i)
		nb_edges += (g->edges[node][i] != 0);
	printf("%s\n%d\n", g->nodes[node], nb_edges);
	for (int i = 0; i < g->nb_nodes; ++i)
		if (g->edges[node][i] != 0)
			printf("%d %d\n", i + 1, g->edges[node][i]);
}

void	print_graph(t_graph *g)
{
	printf("%d\n", g->nb_nodes);
	for (int i = 0; i < g->nb_nodes; ++i)
		print_node(g, i);
}

/*
** We want to make sure e != s, so the same node isn't both the start and the end.
*/

void	print_requests(t_graph *g)
{
	int	nb_req = RNG(MAX_REQ, MIN_REQ);
	int	s, e;

	printf("%d\n", nb_req);
	for (int i = 0; i < nb_req; ++i)
	{
		s = RNG(g->nb_nodes, 0);
		do e = RNG(g->nb_nodes, 0);
		while (s == e);
		printf("%s %s\n", g->nodes[s], g->nodes[e]);
	}
}

/*********************************** MAIN *************************************/

void	free_graph(t_graph *g)
{
	for (int i = 0; i < g->nb_nodes; ++i)
	{
		free(g->nodes[i]);
		free(g->edges[i]);
	}
	free(g->nodes);
	free(g->edges);
}

int		main(int argc, char **argv)
{
	int		nb_tests;
	t_graph	g;

	if (argc == 2)
	{
		nb_tests = atoi(argv[1]);
		printf("%d\n", nb_tests);
		srand(time(NULL));
		while (--nb_tests >= 0)
		{
			g = (t_graph){NULL, NULL, 0};
			gen_graph(&g);
			print_graph(&g);
			print_requests(&g);
			if (nb_tests != 0)
				printf("\n");
#ifdef DEBUG
			print_matrix(g.edges, g.nb_nodes);
#endif
			free_graph(&g);
		}
	}
	return (EXIT_SUCCESS);
}
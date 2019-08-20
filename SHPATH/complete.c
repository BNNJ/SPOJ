#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// #define DEBUG

typedef struct	s_node
{
	char			name[16];
	int				cost;
	int				index;
	int				*links;
	int				nb_links;
	int				visited;
	struct s_node	*next;
}				t_node;

typedef struct	s_graph
{
	t_node			*nodes;
	int				**edges;
	int				nb_nodes;
}				t_graph;

void		print_matrix(int **m, int size)
{
	printf("----- MATRIX -----\nsize: %d\n", size);
	printf("    ");
	for (int i = 0; i < size; ++i)
		printf("%4d", i);
	printf("\n");
	for (int i = 0; i < size; ++i)
	{
		printf("%4d", i);
		for (int j = 0; j < size; ++j)
			printf("%4d", m[i][j]);
		printf("\n");
	}
}

/*************************** HEAP HANDLING ************************************/

static t_node		*heap[10000];
static int			heap_size = 0;

#define parent(x)	((x - 1) / 2)
#define left_ch(x)	(2 * x + 1)
#define right_ch(x)	(2 * x + 2)
#define first		heap[0]
#define last		heap[heap_size - 1]

static void	h_swap(int a, int b)
{
	t_node	*tmp = heap[a];
	heap[a] = heap[b];
	heap[b] = tmp;
}

int			queue_is_empty(void)
{
	return (heap_size == 0);
}

void		heapify(int	n)
{
	int		left = left_ch(n);
	int		right = right_ch(n);
	int		smallest = n;

	if (left < heap_size && heap[left]->cost < heap[smallest]->cost)
		smallest = left;
	if (right < heap_size && heap[right]->cost < heap[smallest]->cost)
		smallest = right;
	if (smallest != n)
	{
		h_swap(smallest, n);
		heapify(smallest);
	}
}

void		push(t_node *node)
{
	int	i, p;

	heap[heap_size] = node;
	i = heap_size;
	++heap_size;
	while ((p = parent(i)) >= 0 && heap[p]->cost > heap[i]->cost)
	{
		h_swap(p, i);
		i = p;
	}
}

t_node		*pop(void)
{
	t_node	*n = first;

	first = last;
	last = NULL;
	--heap_size;
	heapify(0);
	return (n);
}

/******************************* SOLVER ***************************************/

void		update_neighbors(t_graph *g, t_node *c)
{
	t_node	*n;

	for (int i = 0; i < c->nb_links; ++i)
	{
		n = &g->nodes[c->links[i]];
		if (n->cost > c->cost + g->edges[c->index][n->index])
		{
			n->cost = c->cost + g->edges[c->index][n->index];
			push(n);
		}
	}
}

void		find_path(t_graph *g, int s, int e)
{
	t_node	*c = NULL;

#ifdef DEBUG
	printf("------------------------------\n");
	printf("start:	%d %s\nend:	%d %s\n", s, g->nodes[s].name, e, g->nodes[e].name);
#endif

	g->nodes[s].cost = 0;
	push(&g->nodes[s]);
	while (heap_size > 0 && c != &g->nodes[e])
	{
		c = pop();
		if (c->visited == 0)
		{
			c->visited = 1;
			update_neighbors(g, c);
		}
	}
	if (c == &g->nodes[e])
		printf("%d\n", c->cost);
	else
		printf("no path found\n");
}

/*
void		find_path(t_graph *g, int s, int e)
{
	printf("start: %d %s\nend: %d %s\n", s, g->nodes[s].name, e, g->nodes[e].name);
	for (int i = 0; i < g->nb_nodes; ++i)
		printf("%d %s\n", g->nodes[i].index, g->nodes[i].name);
}
*/

void		solve(t_graph *g)
{
	char	start[16], end[16];
	int		s, e;


	scanf("%s %s", start, end);
	for (int i = 0; i < g->nb_nodes; ++i)
	{
		g->nodes[i].cost = INT_MAX;
		g->nodes[i].next = NULL;
		g->nodes[i].visited = 0;
		if (strcmp(start, g->nodes[i].name) == 0)
			s = i;
		else if (strcmp(end, g->nodes[i].name) == 0)
			e = i;
	}
#ifdef DEBUG
	printf("start: %d end: %d\n", s, e);
#endif
	find_path(g, s, e);
}

/********************************* MAIN ***************************************/

int			create_node(t_node *n, int i, int **edges)
{
	int	index, cost;

	n->index = i;
	scanf("%s", n->name);
	scanf("%d", &n->nb_links);
#ifdef DEBUG
	printf("----------\n%d %s\n", i, n->name);
#endif
	if (!(n->links = malloc(sizeof(int) * n->nb_links)))
		return (0);
	for (int j = 0; j < n->nb_links; ++j)
	{
		scanf("%d %d", &index, &cost);
		--index;
		n->links[j] = index;
#ifdef DEBUG
		printf(">> %d / %d <<\n", j, n->nb_links);
		printf(">>>> %d / %d : %d <<\n", i, index, cost);
#endif
		edges[i][index] = cost;
	}
	return (1);
}

int			error_exit(char *msg)
{
	if (msg)
		printf("%s\n", msg);
	return (EXIT_FAILURE);
}

int			main(void)
{
	int		nb_tests = 0, nb_paths = 0;
	t_graph	graph;

	scanf("%d",&nb_tests);
	while (--nb_tests >= 0)
	{
		graph = (t_graph){0};
		scanf("%d", &graph.nb_nodes);
#ifdef DEBUG
		printf("nb_nodes: %d\n", graph.nb_nodes);
#endif
		if (!(graph.nodes = malloc(sizeof(t_node) * graph.nb_nodes)))
			return (error_exit("nodes malloc\n"));

		if (!(graph.edges = malloc(sizeof(int*) * graph.nb_nodes)))
			return (error_exit("matrix malloc\n"));
		for (int i = 0; i < graph.nb_nodes; ++i)
			if (!(graph.edges[i] = calloc(sizeof(int), graph.nb_nodes)))
				return (error_exit("edge malloc\n"));

		for (int i = 0; i < graph.nb_nodes; ++i)
			if (!(create_node(&graph.nodes[i], i, graph.edges)))
				return (error_exit("create_node\n"));
		scanf("%d", &nb_paths);
#ifdef DEBUG
		printf("%d\n", nb_paths);
#endif
//		print_matrix(graph.edges, graph.nb_nodes);
		while (--nb_paths >= 0)
			solve(&graph);
		scanf("%d", &nb_paths);
	}
	return (EXIT_SUCCESS);
}

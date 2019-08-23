#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


typedef struct	s_node
{
	char			name[16];
	char			visited;
	int				cost;
	int				index;
	int				nb_links;
	int				*links;
	struct s_node	*next;
}				t_node;

typedef struct	s_graph
{
	t_node			**nodes;
	int				**edges;
	int				nb_nodes;
}				t_graph;

/******************************* DEBUG ****************************************/

//#define DEBUG
// #define MATRIX

void		print_graph(t_graph *g)
{
	t_node	*tmp;
	t_node	*link;

	printf("nb_nodes: %d\n", g->nb_nodes);
	for (int i = 0; i < g->nb_nodes; ++i)
	{
		tmp = g->nodes[i];
		printf("node %d: %s\n", tmp->index, tmp->name);
		for (int j = 0; j < tmp->nb_links; ++j)
		{
			link = g->nodes[tmp->links[j]];
			printf(">> %d %s : %d\n", link->index, link->name, g->edges[i][link->index]);
		}
	}
}

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

/****************************** HEAP HANDLING *********************************/

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

/******************************** SOLVER **************************************/

void		find_path(t_graph *g, t_node *s, t_node *e)
{
	t_node	*c = NULL;
	t_node	*n = NULL;

	s->cost = 0;
	push(s);
//	printf("start: %s end: %s\n", s->name, e->name);
	while (heap_size > 0)
	{
		c = pop();
		if (c == e)
			break ;
		if (c->visited == 0)
		{
			c->visited = 1;
//			printf("> %d %s\n", c->index, c->name);
			for (int i = 0; i < c->nb_links; ++i)
			{
				n = g->nodes[c->links[i]];
				if (n->cost > c->cost + g->edges[c->index][n->index])
				{
					n->cost = c->cost + g->edges[c->index][n->index];
//					printf(">> %d %s %d\n", n->index, n->name, n->cost);
					push(n);
				}
			}
//			printf(">\n");
		}
	}
	if (c == e)
		printf("%d\n", e->cost);
	else
		printf("no path found\n");
}

void		solve(t_graph *g)
{
	char	buff_s[16], buff_e[16];
	int		s, e;

	memset(heap, 0, sizeof(heap));
	heap_size = 0;
	scanf("%s %s", buff_s, buff_e);
	for	(int i = 0; i < g->nb_nodes; ++i)
	{
		g->nodes[i]->cost = INT_MAX;
		g->nodes[i]->visited = 0;
		if (strcmp(buff_s, g->nodes[i]->name) == 0)
		{
			s = i;
#ifdef DEBUG
			printf("start found: %d %s\n", s, g->nodes[s]->name);
#endif
		}
		else if (strcmp(buff_e, g->nodes[i]->name) == 0)
		{
			e = i;
#ifdef DEBUG
			printf("end found: %d %s\n", e, g->nodes[e]->name);
#endif
		}
	}
	find_path(g, g->nodes[s], g->nodes[e]);
}

/******************************** PARSER **************************************/

static t_node	*get_node(int **edges, int i)
{
	t_node	*n;
	int		cost, j;

	if (!(n = malloc(sizeof(t_node))))
		return (NULL);
	n->index = i;
	scanf("%s", n->name);
	scanf("%d", &n->nb_links);
	if (!(n->links = malloc(sizeof(int) * n->nb_links)))
		return (NULL);
	for (int k = 0; k < n->nb_links; ++k)
	{
		scanf("%d %d", &j, &cost);
		--j;
		edges[i][j] = cost;
		n->links[k] = j;
	}
	return (n);
}

int		get_graph(t_graph *g)
{
	scanf("%d", &g->nb_nodes);
	if (!(g->nodes = malloc(sizeof(t_node*) * g->nb_nodes)))
		return (0);
	if (!(g->edges = malloc(sizeof(int*) * g->nb_nodes)))
		return (0);
	for (int i = 0; i < g->nb_nodes; ++i)
		if (!(g->edges[i] = calloc(sizeof(int), g->nb_nodes)))
			return (0);
	for (int i = 0; i < g->nb_nodes; ++i)
		g->nodes[i] = get_node(g->edges, i);
	return (1);
}

/********************************* MAIN ***************************************/

int			error_exit(char *msg)
{
	if (msg)
		printf("%s\n", msg);
	return (EXIT_FAILURE);
}

int			main(void)
{
	int		nb_tests, nb_req;
	t_graph	g;

	scanf("%d", &nb_tests);
	while (--nb_tests >= 0)
	{
#ifdef DEBUG
		printf("---- NEW TEST ----\n");
#endif
		get_graph(&g);
#ifdef DEBUG
		print_graph(&g);
		print_matrix(g.edges, g.nb_nodes);
#endif
		scanf("%d", &nb_req);
		while (--nb_req >= 0)
			solve(&g);
//		scanf("%d", &nb_req);
	}
	return (EXIT_SUCCESS);
}

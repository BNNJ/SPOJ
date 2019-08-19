#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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

#define HEAP

/*************************** HEAP HANDLING ************************************/

#ifdef HEAP

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

/******************************** QUEUE ***************************************/
#elif

t_node	*queue = NULL;

static inline void		push(t_node *node)
{
	t_node	*cur = queue;
	
	if (cur == NULL)
		queue = node;
	else
	{
		while (cur->next && cur->next->cost < node->cost)
		{
			printf("%d\n", cur->index);
			cur = cur->next;
		}
		if (cur == NULL)
		{
			node->next = queue;
			queue = node;
		}
		else
		{
			node->next = cur->next;
			cur->next = node;
		}
	}
}

static inline t_node	*pop()
{
	t_node	*node = queue;
	queue = queue->next;
	node->next = NULL;
	return (node);
}

static inline int		queue_is_empty()
{
	return (queue == NULL);
}

#endif
/******************************* SOLVER ***************************************/

void		update_neighbors(t_graph *g, t_node *c)
{
	t_node	*n;

	for (int i = 0; i < c->nb_links; ++i)
	{
		n = &g->nodes[c->links[i]];
		if (n->cost > c->cost + g->edges[n->index][c->index])
			n->cost = c->cost + g->edges[n->index][c->index];
		if (n->visited == 0)
			push(n);
	}
}

void		find_path(t_graph *g, int s, int e)
{
	t_node	*c = NULL;

	printf("------------------------------\n");
	printf("start:	%d %s\nend:	%d %s\n", s, g->nodes[s].name, e, g->nodes[e].name);
	g->nodes[s].cost = 0;
	push(&g->nodes[s]);
	while (!queue_is_empty() && c != &g->nodes[e])
	{
		c = pop();
		if (c->visited == 0)
		{
			c->visited = 1;
			update_neighbors(g, c);
		}
	}
	if (c->index == e)
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
	find_path(g, s, e);
}

/********************************* MAIN ***************************************/

int			create_node(t_node *n, int i, int **edges)
{
	int	index, cost;

	n->index = i;
	scanf("%s", n->name);
	scanf("%d", &n->nb_links);
	if (!(n->links = malloc(sizeof(int) * n->nb_links)))
		return (0);
	for (int j = 0; j < n->nb_links; ++j)
	{
		scanf("%d %d", &index, &cost);
		--index;
		n->links[j] = index;
//		printf(">> %d / %d <<\n", j, n->nb_links);
//		printf(">>>> %d / %d : %d <<\n", i, index, cost);
		edges[i][index] = cost;
		edges[index][i] = cost;
	}
//	printf("HELLO\n");
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
	char	tmp[8];

	scanf("%d",&nb_tests);
	while (--nb_tests >= 0)
	{
		graph = (t_graph){0};
		scanf("%d", &graph.nb_nodes);

		printf("nb_nodes: %d\n", graph.nb_nodes);

		if (!(graph.nodes = malloc(sizeof(t_node) * graph.nb_nodes)))
			return (error_exit("nodes malloc\n"));

		if (!(graph.edges = malloc(sizeof(int*) * graph.nb_nodes)))
			return (error_exit("matrix malloc\n"));
		for (int i = 0; i < graph.nb_nodes; ++i)
			if (!(graph.edges[i] = malloc(sizeof(int) * graph.nb_nodes)))
				return (error_exit("edge malloc\n"));

		for (int i = 0; i < graph.nb_nodes; ++i)
			if (!(create_node(&graph.nodes[i], i, graph.edges)))
				return (error_exit("create_node\n"));
		scanf("%d", &nb_paths);
		while (--nb_paths >= 0)
			solve(&graph);

		scanf("%s\n", tmp);
	}
	return (EXIT_SUCCESS);
}

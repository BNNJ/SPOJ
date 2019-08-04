#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 1024

static int	stack_i;
static int	queue_i;
static char	stack[BUFF_SIZE];
static char	input[BUFF_SIZE];
static char	output[BUFF_SIZE];

#define is_op(x)		x == '*' || x == '/' || x == '+' || x == '-' || x == '^'
#define q_push(x)		output[queue_i++] = x
#define s_push(x)		stack[stack_i++] = x
#define s_pop()			stack[--stack_i]
#define s_peek()		stack[stack_i - 1]

static inline int	get_prio(char op)
{
	int	prio;

	if (op == '+' || op == '-')
		prio = 1;
	else if (op == '*' || op == '/')
		prio = 2;
	else if (op == '^')
		prio = 3;
	else
		prio = 0;
	return (prio);
}

static inline void	handle_op(char op)
{
	int	prio = get_prio(op);

	while (get_prio(s_peek()) > prio)
		q_push(s_pop());
	s_push(op);
}

static void			init_stuff(void)
{
	stack_i = 0;
	queue_i = 0;
	memset(stack, 0, BUFF_SIZE);
	memset(input, 0, BUFF_SIZE);
	memset(output, 0, BUFF_SIZE);
}

int		main(void)
{
	int		i = 0;
	char	c;
	int		nb_test;


	fgets(input, BUFF_SIZE, stdin);
	nb_test = atoi(input);
	while (--nb_test >= 0)
	{
		init_stuff();
		i = 0;
		fgets(input, BUFF_SIZE, stdin);
		while ((c = input[i]) != 0)
		{
			if (is_op(c))
				handle_op(c);
			else if (c == '(')
				s_push('(');
			else if (c == ')')
				while ((c = s_pop()) != '(')
					q_push(c);
			else if ((c >= 'a' && c <= 'z') || (c >= '0' && c<= '9'))
				q_push(c);
			++i;
		}
		while (i-- >= 0)
			q_push(s_pop());
		printf("%s\n", output);
	}
	return (EXIT_SUCCESS);
}

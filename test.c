
#include <stdlib.h>
#include <stdio.h>

typedef char	t_bool;

typedef struct		s_script
{
	t_bool		opt_q;
	t_bool		opt_a;
	int			fd;
	char		**cmd;
}					t_script;

void			get_opt(char **av, t_script *script)
{
	int			i;
	int			j;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			j = 1;
			while (av[i][j])
			{
				if (av[i][j] == 'a')
					script->opt_a = 1;
				else if (av[i][j] == 'q')
					script->opt_q = 1;
				else
					exit(ft_putstr_fd(USAGE));
				j++;
			}

		}
	}
}

int				open_error(void)
{
	ft_putstr_fd("error opening file\n");
	return (-1);
}

int				get_fd(char *name, int flag)
{
	int		fd;

	fd = -1;
	if (flag)
	{
		if ((fd = open(name, O_CREAT | O_RDWR | O_APPEND)) == -1)
			exit(open_error());
	}
	else
	{
		if ((fd = open(name, O_CREAT | O_RDWR | O_TRUNC)) == -1)
			exit(open_error());
	}
	return (fd);
}

void			fill_script(char **str, t_script *script)
{
	static char		file_flag = 0;
	static char		cmd_flag = 0;

	if (**str != '-' && !file_flag)
	{
		script->fd = get_fd(*str, script->opt_a);
		file_flag = 1;
	}
	else if (**str != '-' && file_flag && !cmd_flag)
	{
		script->cmd = str;
		cmd_flag == 1;
	}
}

t_script		*init_script(char **av)
{
	t_script	*new;
	int			i;

	i = 1;
	if ((new = (t_script*)(ft_malloc(sizeof(*script)))) == NULL)
		return (NULL);
	new->opt_q = 0;
	new->opt_a = 0;
	new->fd = -1;
	new->cmd = NULL;
	get_opt(av, script);
	while (av[i])
	{
		fill_script(av + i, new);
		i++;
	}
	return (script);
}

char			**get_shell(void)
{

}

int				check_script(t_script *script)
{
	if (script->fd == -1)
	{
		if (script->opt_a)
		{
			if ((script->fd = open("typescript", O_CREAT | O_RDWR | O_APPEND)) == -1)
				return (-1);
		}
		else if (!(script->opt_a))
		{
			if ((script->fd = open("typescript", O_CREAT | O_RDWR | O_TRUNC)) == -1)
				return (-1);
		}
	}
	if (script->cmd == NULL)
		script->cmd = get_shell();
	return (0);
}

int 			main (int argc, char **argv)
{
	t_script		*script;

	(void)argc;
	script = init_script(argc, argv);
	if (check_script(script))
		exit(-1);
//	script = (t_script*)(malloc(sizeof(*script)));
//	script->cmd = argv + 1;
//	test_fn(script);
	return (0);
}

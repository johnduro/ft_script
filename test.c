/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/01 18:49:01 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/05/02 17:40:15 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

int				error_usage(void)
{
	ft_putstr_fd(USAGE, 2);
	return (-1);
}

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
					exit(error_usage());
				j++;
			}
		}
		else if (av[i][0] != '-')
			break ;
		i++;
	}
}

int				open_error(void)
{
	ft_putstr_fd("error opening file\n", 2);
	return (-1);
}

int				get_fd(char *name, int flag)
{
	int		fd;

	fd = -1;
	if (flag)
	{
		if ((fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
			exit(open_error());
	}
	else
	{
		if ((fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1)
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
		script->name = *str;
		file_flag = 1;
	}
	else if (**str != '-' && file_flag && !cmd_flag)
	{
		script->cmd = str;
		cmd_flag = 1;
	}
}

t_script		*init_script(char **av)
{
	t_script	*new;
	int			i;

	i = 1;
	if ((new = (t_script*)(ft_malloc(sizeof(t_script)))) == NULL)
		return (NULL);
	new->opt_q = 0;
	new->opt_a = 0;
	new->fd = -1;
	new->cmd = NULL;
	get_opt(av, new);
	while (av[i])
	{
		fill_script(av + i, new);
		i++;
	}
	return (new);
}

char			*get_shell(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHELL=", 6))
			return (&env[i][6]);
		i++;
	}
	return (NULL);
}

int				check_script(t_script *script)
{
	if (script->fd == -1)
	{
		if (script->opt_a)
		{
			if ((script->fd = open("typescript", O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
				return (-1);
		}
		else if (!(script->opt_a))
		{
			if ((script->fd = open("typescript", O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1)
				return (-1);
		}
		script->name = m_strdup("typescript");
	}
	return (0);
}

int 			main(int argc, char **argv, char **env)
{
	t_script		*script;

	(void)argc;
	script = init_script(argv);
	if (check_script(script))
		return (-1);
	if (!(script->shell = get_shell(env)))
	{
		printf("NULL environement !\n");
		return (-1);
	}
	ft_script(script);
	return (0);
}

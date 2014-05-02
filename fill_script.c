/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 19:23:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 19:32:31 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "script.h"

static int			error_usage(void)
{
	ft_putstr_fd(USAGE, 2);
	return (-1);
}

void				get_opt(char **av, t_script *script)
{
	int		i;
	int		j;

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

static int			open_error(void)
{
	ft_putstr_fd("error opening file\n", 2);
	return (-1);
}

static int			get_fd(char *name, int flag)
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

void				fill_script(char **str, t_script *script)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 18:57:37 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 19:18:53 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "script.h"

static t_script		*init_script(char **av)
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

int					check_script(t_script *script)
{
	if (script->fd == -1)
	{
		if (script->opt_a)
		{
			if ((script->fd = open("typescript",
								O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
				return (-1);
		}
		else if (!(script->opt_a))
		{
			if ((script->fd = open("typescript",
								O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1)
				return (-1);
		}
		script->name = m_strdup("typescript");
	}
	return (0);
}

int					main(int argc, char **argv, char **env)
{
	t_script	*script;

	(void)argc;
	script = init_script(argv);
	if (check_script(script))
		return (-1);
//	if (!(script->shell = get_shell(env)))
	if (!(script->shell = m_getenv("SHELL", env)))
	{
		printf("NULL environement !\n");
		return (-1);
	}
	ft_script(script);
	return (0);
}

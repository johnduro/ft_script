/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 18:51:06 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 18:54:58 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "script.h"

char			*m_getenv(char *var, char **env)
{
	char		**tmp;
	char		*value;
	int			len;

	value = NULL;
	tmp = env;
	while (*tmp)
	{
		if ((ft_strnequ(*tmp, var, (len = ft_strlen(var))) == 1))
		{
			if ((*tmp)[len + 1] == '=')
				len++;
			value = m_strdup((*tmp) + len + 1);
			return (value);
		}
		tmp++;
	}
	return (value);
}

static int		sc_do_command(char *path, char **req, char **env)
{
	if (execve(path, req, env) == -1)
		exit(-1);
	return (0);
}

static int		access_error(char *name, char **path)
{
	char		*tmp;

	if (access(name, F_OK) == 0 && access(name, X_OK) != 0)
	{
		write(2, name, ft_strlen(name));
		write(2, ": you don't have the rights to execute\n", 39);
		return (-1);
	}
	while (*path)
	{
		tmp = m_strjoinwsep(*path, name, '/');
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) != 0)
		{
			write(2, name, ft_strlen(name));
			write(2, ": you don't have the rights to execute\n", 39);
			ft_free(tmp);
			return (-1);
		}
		ft_free(tmp);
		path++;
	}
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
	return (-1);
}

static int		check_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}

void			script_cmd(t_script *script, char **env)
{
	char		*tmp;
	char		**path;
	char		**bws_path;

	tmp = m_getenv("PATH", env);
	path = m_strsplit(tmp, ':');
	ft_free(tmp);
	bws_path = path;
	if (check_access(*(script->cmd)))
		exit(sc_do_command(*(script->cmd), script->cmd, env));
	while (*bws_path)
	{
		tmp = m_strjoinwsep(*bws_path, *(script->cmd), '/');
		if (check_access(tmp))
		{
			sc_do_command(tmp, script->cmd, env);
			exit(-1);
		}
		ft_free(tmp);
		bws_path++;
	}
	exit(access_error(*(script->cmd), path));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 18:17:09 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 19:39:52 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

static void		ft_print(int bol, t_script *script)
{
	char		*timing;
	time_t		current;

	if (script->opt_q)
		return ;
	time(&current);
	timing = ctime(&current);
	if (bol)
	{
		ft_putstr("Script started, output file is ");
		ft_putendl(script->name);
		ft_putstr_fd("Script started on ", script->fd);
		ft_putstr_fd(timing, script->fd);
	}
	else
	{
		ft_putstr("\nScript done, output file is ");
		ft_putendl(script->name);
		ft_putstr_fd("Script done on ", script->fd);
		ft_putendl_fd(timing, script->fd);
	}
}

static void		make_connex(int fdm, t_script *script, fd_set *set, int pid)
{
	char		buf[65];
	int			ret;

	while (waitpid(pid, &ret, WNOHANG) != pid)
	{
		FD_SET(0, set);
		FD_SET(fdm, set);
		select(fdm + 1, set, NULL, NULL, NULL);
		if (FD_ISSET(0, set))
		{
			ret = read(0, buf, 64);
			if (ret > 0)
				write(fdm, buf, ret);
		}
		if (FD_ISSET(fdm, set))
		{
			ret = read(fdm, buf, 64);
			if (ret > 0)
			{
				write(1, buf, ret);
				write(script->fd, buf, ret);
			}
		}
	}
}

static void		exec_script(t_script *script, int fdm, int fds)
{
	extern char		**environ;
	char			*arg[2];

	close(fdm);
	ft_login_tty(fds);
	if (script->cmd == NULL)
	{
		arg[0] = ft_strrchr(script->shell, '/') + 1;
		arg[1] = NULL;
		execve(script->shell, arg, environ);
	}
	else
		script_cmd(script, environ);
	exit(3);
}

void			ft_script(t_script *script)
{
	int		fdm;
	int		fds;
	int		pid;
	fd_set	set;

	if (ft_open_pts(&fdm, &fds) == -1)
		_exit(1);
	ft_print(1, script);
	if ((pid = fork()) == 0)
		exec_script(script, fdm, fds);
	close(fds);
	ft_init_term();
	FD_ZERO(&set);
	make_connex(fdm, script, &set, pid);
	ft_print(0, script);
	ft_def_term();
	_exit(0);
}

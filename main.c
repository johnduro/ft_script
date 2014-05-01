/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 17:22:59 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/01 20:35:50 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

void		ft_print(int bol, t_script *script)
{
	char	*timing;
	time_t	current;

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
		ft_putstr(script->name);
		ft_putstr_fd("Script done on ", script->fd);
		ft_putendl_fd(timing, script->fd);
	}
}

void		ft_script(t_script *script)
{
	int		fdm;
	int		fds;
	int		pid;
	int		i;
	fd_set	set;
	char	buf[64];

	if (ft_open_pts(&fdm, &fds) == -1) //DONE
		_exit(1);
	ft_print(1, script);
	if ((pid = fork()) < 0)
		_exit(2);
	if (!pid)
	{
	// child
		close(fdm);
		ft_login_tty(fds); //DONE
		execl(script->shell, ft_strrchr(script->shell, '/') + 1, NULL);
		exit(3);
	}
	/* father: copy stdin/out to/from master */
	close(fds);
	//system("stty raw -echo"); //a refaire man 3 -> surement des modification des termcaps void man
	ft_init_term();
	FD_ZERO(&set);
	while (waitpid(pid, &i, WNOHANG)!=pid)
	{
		FD_SET(0, &set);
		FD_SET(fdm, &set);
		select(fdm+1, &set, NULL, NULL, NULL);
		if (FD_ISSET(0, &set))
		{
			i = read(0, buf, 64);
			if (i>0)
				write(fdm, buf, i);
		}
		if (FD_ISSET(fdm, &set))
		{
			i = read(fdm, buf, 64);
			if (i>0)
			{
				write(1, buf, i);
				write(script->fd, buf, i);
			}
		}
	}
	ft_print(0, script);
	//system("stty sane"); //a refaire man 3 surement termcaps
	ft_def_term();
	_exit(0);
}

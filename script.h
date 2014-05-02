/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/01 18:52:54 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/05/01 20:41:53 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCRIPT_H
# define SCRIPT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <utmp.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <util.h>
# include <time.h>
# include <libft.h>
# include "ft_malloc.h"

# define USAGE "Please use it right\nft_script [ -option ] [ file [command] ]\n"

typedef char	t_bool;

typedef struct		s_script
{
	t_bool			opt_q;
	t_bool			opt_a;
	int				fd;
	char			**cmd;
	char			*name;
	char			*shell;
}					t_script;

void				ft_script(t_script *script);
int					ft_open_pts(int *fdm, int *fds);
int					ft_login_tty(int fd);
char				*m_strdup(const char *s);
void				ft_init_term();
void				ft_def_term();

#endif

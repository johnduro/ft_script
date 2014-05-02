/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 18:56:31 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 19:34:00 by mle-roy          ###   ########.fr       */
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

# define USAGE "ft_script [ -aq (option) ] [ file [command] ]\n"

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
void				ft_init_term(void);
void				ft_def_term(void);
char				*m_strsub(char const *s, unsigned int start, size_t len);
char				*m_strnew(size_t size);
char				*m_strjoinwsep(char const *s1, char const *s2, char sep);
char				**m_strsplit(char const *s, char c);
char				*m_getenv(char *var, char **env);
char				*m_getenv(char *var, char **env);
void				fill_script(char **str, t_script *script);
void				get_opt(char **av, t_script *script);
void				script_cmd(t_script *Script, char **env);

#endif

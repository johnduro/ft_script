/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 17:22:59 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 17:45:35 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"
#include "ft_malloc.h"

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

char			*m_getenv(char *var, char **env)
{
	char			**tmp;
	char			*value;
	int				len;

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

char	*m_strsub(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

	i = 0;
	newstr = (char *)ft_malloc(sizeof(newstr) * len + 1);
	if (newstr == NULL)
		return (NULL);
	while (i < len)
	{
		newstr[i] = s[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}

static size_t	ft_strlenws(char const *s, char c)
{
	size_t		result;

	result = 0;
	while (*s != c && *s)
	{
		result++;
		s++;
	}
	return (result);
}

static char		**ft_spliting(char const *s, char **newt, char c)
{
	unsigned int	i;
	int				x;

	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			newt[x++] = m_strsub(s, i, ft_strlenws(&s[i], c));
			i = i + ft_strlenws(&s[i], c);
		}
		else
			i++;
	}
	return (newt);
}

char	**m_strsplit(char const *s, char c)
{
	int		i;
	int		t;
	char	**newtab;

	i = 0;
	t = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && ((i != 0 && s[i - 1] == c) || i == 0))
			t++;
		i++;
	}
	newtab = (char**)(ft_malloc(sizeof(newtab) * (t + 1)));
	if (newtab == NULL)
		return (NULL);
	while (t != -1)
		newtab[t--] = '\0';
	newtab = ft_spliting(s, newtab, c);
	return (newtab);
}

int				check_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}

char	*m_strnew(size_t size)
{
	char	*newstr;
	size_t	i;

	i = 0;
	newstr = (char *)ft_malloc(sizeof(newstr) * size + 1);
	if (newstr == NULL)
		return (NULL);
	while (i <= size)
	{
		newstr[i] = '\0';
		i++;
	}
	newstr[size] = '\0';
	return (newstr);
}

char	*m_strjoinwsep(char const *s1, char const *s2, char sep)
{
	char	*str;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	str = m_strnew(s1_len + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	str[s1_len] = sep;
	ft_strcat(str, s2);
	return (str);
}

int		sc_do_command(char *path, char **req, char **env)
{
	if (execve(path, req, env) == -1)
		exit(-1);
	return (0);
}

void		script_cmd(t_script *script, char **env)
{
	char	*tmp;
	char	**path;
	char	**bws_path;

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
//	exit(access_error(*(inst->arg), tree->path)); //gestion erreur ?
}

void		exec_script(t_script *script, int fdm, int fds)
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

void		make_connex(int fdm, t_script *script, fd_set *set, int pid)
{
	char	buf[64];
	int 	ret;

	while (waitpid(pid, &ret, WNOHANG) != pid)
	{
		FD_SET(0, set);
		FD_SET(fdm, set);
		select(fdm+1, set, NULL, NULL, NULL);
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

void		ft_script(t_script *script)
{
	int			fdm;
	int			fds;
	int			pid;
	fd_set		set;

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

/*
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
		_exit(3);
	}
	// father: copy stdin/out to/from master
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
*/

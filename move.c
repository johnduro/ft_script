/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/29 19:28:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 18:04:02 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <grp.h>
#include "libft.h"

int		ft_login_tty(int fd)
{
	setsid();
	if (ioctl(fd, TIOCSCTTY, NULL) == -1)
		return (-1);
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);
	return (0);
}

char	*ft_ptsname(int fdm)
{
	static char		ret[128];

	if (ioctl(fdm, TIOCPTYGNAME, ret) < 0)
		return (NULL);
	return (ret);
}

int		ft_open_pts(int *fdm, int *fds)
{
	if ((*fdm = open("/dev/ptmx", O_RDWR | O_NOCTTY)) < 0)
		return (-1);
	ioctl(*fdm, TIOCPTYGRANT);
	ioctl(*fdm, TIOCPTYUNLK);
	if ((*fds = open(ft_ptsname(*fdm), O_RDWR | O_NOCTTY)) == -1)
	{
		write(1, "fds error\n", 10);
		return (-1);
	}
	return (0);
}

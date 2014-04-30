/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/29 19:28:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/30 17:16:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <util.h>
#include "libft.h"
#include <stdio.h>

#define BUFF_SIZE 1024

int		main(void)
{
	struct termios		term;
	struct winsize		winp;
	char				*name;
	int					master;
	int					slave;
	int					fd;

	fd = open("/dev/ptmx", O_RDONLY);
	printf("fd= %d\n", fd);
	return (0);
}*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

int		main()
{
	int zero=0;
	char name[16];
	int fds, fdm;
	char	*real;

	if ((fdm = open("/dev/ptmx", O_RDWR)) < 0)
		exit(1);

	real = ptsname(fdm);
	if (ioctl(fdm, TIOCPTYGNAME, name) < 0)
		exit(2);
	//real = ptsname(fdm);
//	sprintf(name, "/dev/pts/%i", n);
	printf("name= %s\nreal=%s\n", name, real);
	if (ioctl(fdm, TIOCPTYUNLK, &zero) < 0)
	exit(3);

	if ((fds = open(name, O_RDWR)) < 0)
		exit(4);
	exit(0);
}

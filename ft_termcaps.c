/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 19:58:15 by nsavry            #+#    #+#             */
/*   Updated: 2014/05/02 17:52:11 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "script.h"

void		ft_init_term(void)
{
	struct termios				tattr;
	static struct termios		*temp = NULL;

	ioctl(0, TIOCGETA, &tattr);
	temp = ft_malloc(sizeof(struct termios));
	*temp = tattr;
	tattr.c_lflag &= ~(ECHO | ICANON);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	ioctl(0, TIOCSETA, &tattr);
}

void		ft_def_term(void)
{
	struct termios	tattr;

	ioctl(0, TIOCGETA, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	ioctl(0, TIOCSETA, &tattr);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_strdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:28:41 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/01 19:33:01 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "ft_malloc.h"

char	*m_strdup(const char *s)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = ft_malloc(sizeof(s2) * ft_strlen(s) + 1);
	if (s2 == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

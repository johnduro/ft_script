/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_strnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 18:46:44 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 19:36:48 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

char		*m_strnew(size_t size)
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

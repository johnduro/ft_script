/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_strsub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 18:41:42 by mle-roy           #+#    #+#             */
/*   Updated: 2014/05/02 19:37:28 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

char		*m_strsub(char const *s, unsigned int start, size_t len)
{
	char		*newstr;
	size_t		i;

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

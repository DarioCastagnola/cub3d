/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:32:14 by mpaterno          #+#    #+#             */
/*   Updated: 2023/09/05 15:06:10 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	if (!s1 && s2)
		return (- (unsigned char) s2[0]);
	else if (s1 && !s2)
		return ((unsigned char) s1[0]);
	else if (!s1 && !s2)
		return (0);
	while (++i < n)
	{
		if (s1[i] != s2[i] || (!s1[i] || !s2[i]))
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:02:14 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/27 14:35:04 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*us;
	size_t			i;

	uc = c;
	us = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (us[i] == uc)
			return ((void *) &us[i]);
		i++;
	}
	return (NULL);
}

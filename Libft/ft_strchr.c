/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:39:57 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/25 14:17:21 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cc;

	cc = (char) c;
	while (*s != '\0' && *s != cc)
		s++;
	if (cc == '\0')
		return ((char *)s);
	if (*s == '\0')
		return (0);
	else
		return ((char *)s);
}

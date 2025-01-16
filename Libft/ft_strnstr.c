/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:27:24 by etom              #+#    #+#             */
/*   Updated: 2024/05/03 12:10:01 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*bbig;

	bbig = (char *)big;
	i = 0;
	if (ft_strlen(little) == 0)
		return (bbig);
	while (big[i] && i < len)
	{
		if (little[0] == big[i])
		{
			j = 0;
			while (little[j] && little[j] == big[i] && big[i] && i < len)
			{
				j++;
				i++;
			}
			if (little[j - 1] == big[i - 1] && little[j] == '\0' && i <= len)
				return (&bbig[i - j]);
			i -= j;
		}
		i++;
	}
	return (0);
}

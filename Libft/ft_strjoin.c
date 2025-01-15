/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etom <etom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:31:09 by etom              #+#    #+#             */
/*   Updated: 2024/04/20 23:57:05 by etom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		n;
	int		i;

	n = 0;
	i = 0;
	res = malloc(sizeof * res * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[n])
	{
		res[n] = s1[n];
		n++;
	}
	while (s2[i])
	{
		res[n] = s2[i];
		n++;
		i++;
	}
	res[n] = '\0';
	return (res);
}

/*int	main(void)
{
	char s1[] = "isso isso isso ";
	char s2[] = "nao nao nao";
	printf("%s", ft_strjoin(s1, s2));
}
*/
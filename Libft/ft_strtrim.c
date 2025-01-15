/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:11:56 by etom              #+#    #+#             */
/*   Updated: 2024/05/03 12:16:36 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chrchk(char c, char const *set)
{
	int	n;

	n = 0;
	while (set[n])
	{
		if (set[n] == c)
			return (1);
		n++;
	}
	return (0);
}

static char	*nstr(char const *s1, size_t start, size_t len)
{
	char	*cpy;
	size_t	c;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	cpy = ft_calloc(len + 1, 1);
	if (!cpy)
		return (NULL);
	c = 0;
	while (c < len)
	{
		cpy[c] = s1[start + c];
		c++;
	}
	return (cpy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		c;
	int		k;

	c = 0;
	k = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (chrchk(s1[c], set) == 1)
		c++;
	while (chrchk(s1[k], set) == 1)
		k--;
	return (nstr(s1, c, k - (c - 1)));
}
/* int main (void)
{
	char *s = ft_strtrim("tripouille   xxx", " x");
	printf("%s", s);
} */
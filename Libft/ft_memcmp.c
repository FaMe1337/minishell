/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etom <etom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:22:09 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/12 22:15:26 by etom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (n - 1 > i && ss1[i] == ss2[i])
		i++;
	if (n == 0 || ss1[i] == ss2[i])
		return (0);
	if (ss1[i] > ss2[i])
		return (1);
	else
		return (-1);
}

/*int	main (void)
{
	printf("%d\n", ft_memcmp("salut", "salut", 5));
	printf("%d\n\n",  memcmp("salut", "salut", 5));
	printf("%d\n", ft_memcmp("t\200", "t\0", 2));
	printf("%d\n\n",  memcmp("t\200", "t\0", 2));
	printf("%d\n", ft_memcmp("testss", "test", 5));
	printf("%d\n\n",  memcmp("testss", "test", 5));
	printf("%d\n", ft_memcmp("test", "tEst", 4));
	printf("%d\n\n",  memcmp("test", "tEst", 4));
	printf("%d\n", ft_memcmp("", "test", 4));
	printf("%d\n\n", memcmp("", "test", 4));
	printf("%d\n", ft_memcmp("test", "", 4));
	printf("%d\n\n", memcmp("test", "", 4));
	printf("%d\n", ft_memcmp("abcdefghij", "abcdefgxyz", 7));
	printf("%d\n\n",  memcmp("abcdefghij", "abcdefgxyz", 7));
	printf("%d\n", ft_memcmp("abcdefgh", "abcdwxyz", 6));
	printf("%d\n\n",  memcmp("abcdefgh", "abcdwxyz", 6));
	printf("%d\n", ft_memcmp("zyxbcdefgh", "abcdefgxyz", 0));
	printf("%d\n",    memcmp("zyxbcdefgh", "abcdefgxyz", 0));
}*/
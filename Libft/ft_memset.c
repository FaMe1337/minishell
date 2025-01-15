/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:12:36 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/24 17:28:40 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/* int main (void)
{
	int i = 0;
	
	int s[100] = {0};
	while (i < 100)
	{
		printf("%d", s[i]);
		i++;
	}
	int *res1 = memset(s, 'A', 42);
	int *res2 = ft_memset(s, 'A', 42);
	
	i = 0;
	printf("\n");
	while (res1[i])
	{
		printf("%c", res1[i]);
		i++;
	}
	i = 0;
	printf("\n");
	while (res2[i])
	{
		printf("%c", res2[i]);
		i++;
	}
	printf("\n");
} */
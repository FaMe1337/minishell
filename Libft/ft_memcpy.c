/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:32:49 by toferrei          #+#    #+#             */
/*   Updated: 2024/05/04 15:53:36 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/* int main (void)
{
	int i = 0;
	
	char s[]= {""};
	char d[] = "o sitio onde o vais copiar";
	printf("%s\n", d);
	char *res1 = memcpy(d, s, sizeof(s));
	
	char *res2 = ft_memcpy(d, s, sizeof(s));

	int s[]= {9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int d[]= {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int *res1 = memcpy(d, s, sizeof(s));
	int *res2 = ft_memcpy(d, s, sizeof(s));

 	printf("%s\n", res1);
	printf("%s\n", res2);
	while (s[i])
	{
		printf("%d", s[i]);
		i++;
	}
	i = 0;
	printf("\n");
	while (res1[i])
	{
		printf("%d", res1[i]);
		i++;
	}
	i = 0;
	printf("\n");
	while (res2[i])
	{
		printf("%d", res2[i]);
		i++;
	}
} */
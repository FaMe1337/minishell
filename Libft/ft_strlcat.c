/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:08:49 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/23 18:00:00 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned long	sizedest;
	unsigned long	sizesrc;
	unsigned long	i;

	i = 0;
	sizedest = ft_strlen(dest);
	sizesrc = ft_strlen(src);
	if (size <= sizedest || size == 0)
		return (sizesrc + size);
	while (src[i] && sizedest + i < (size - 1))
	{
		dest[sizedest + i] = src[i];
		i++;
	}
	dest[sizedest + i] = '\0';
	return (sizedest + sizesrc);
}

/* int main (void)
{
	char *dest1;
	dest1 = (char *)malloc(sizeof(*dest1) * 15);
	memset(dest1, 0, 15);
	memset(dest1, 'r', 6);

	printf("%d\n", (int)ft_strlcpy(dest1, "lorem ipsum dolor sit amet", 0));
	write(1, dest1, 15);
}	
 */
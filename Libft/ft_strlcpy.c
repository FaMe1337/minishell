/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:08:24 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/23 17:59:36 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	n;

	n = ft_strlen ((const char *)src);
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (n);
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
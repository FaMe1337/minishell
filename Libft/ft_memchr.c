/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:02:14 by toferrei          #+#    #+#             */
/*   Updated: 2024/05/04 15:50:52 by toferrei         ###   ########.fr       */
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

/* int	main(void)
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	char s1[] = {0, 1, 2 ,3 ,4 ,5};
	char s2[] = {0, 1, 2 ,3 ,4 ,5};
	char s3[] = {0, 1, 2 ,3 ,4 ,5};
	char s4[] = {0, 1, 2 ,3 ,4 ,5};
	char s5[] = {0, 1, 2 ,3 ,4 ,5};
	char s6[] = {0, 1, 2 ,3 ,4 ,5};
	char s7[] = {0, 1, 2 ,3 ,4 ,5};
	char s8[] = {0, 1, 2 ,3 ,4 ,5};
	char s9[] = {0, 1, 2 ,3 ,4 ,5};

	printf("t1:%p\n", (char*)memchr(s, 0, 0));
	printf("t1:%p\n\n", (char*)ft_memchr(s1, 0, 0));

	printf("t2:%p\n", memchr(s2, 0, 1));
	printf("t2:%p\n\n", ft_memchr(s3, 0, 1));

	printf("t3:%p\n", memchr(s4, 2, 3));
	printf("t3:%p\n\n", ft_memchr(s5, 2, 3));

	printf("t4:%p\n", memchr(s6, 6, 6));
	printf("t4:%p\n\n", ft_memchr(s7, 6, 6));

	printf("t5:%p\n", memchr(s8, 2 + 256, 3));
	printf("t5:%p\n", ft_memchr(s9, 2 + 256, 3));
	
} */

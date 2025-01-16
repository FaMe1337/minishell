/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:39:57 by toferrei          #+#    #+#             */
/*   Updated: 2024/05/03 12:08:23 by toferrei         ###   ########.fr       */
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

/* int	main(void)
{
	char s[] = "tripouille";
	printf("%s\n", strchr("Aqui ha gato", '\0'));
	printf("%s\n\n", ft_strchr("Aqui ha gato", '\0'));
	
	printf("%s\n", strchr(s, 't' + 256));
	printf("%s\n", ft_strchr(s, 't' + 256));
}
 */
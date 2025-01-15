/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:38:13 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/13 18:29:18 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int ch)
{
	if ('A' <= ch && ch <= 'Z')
		return (ch + 32);
	else
		return (ch);
}

/* int	main(void)
{
	printf("%c", ft_tolower('+'));
} */

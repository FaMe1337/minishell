/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:09:28 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/13 18:19:26 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int ch)
{
	if ('a' <= ch && ch <= 'z')
		return (ch - 32);
	else
		return (ch);
}

/* int	main(void)
{
	printf("%c", ft_toupper('+'));
} */

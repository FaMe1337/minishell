/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:12:11 by toferrei          #+#    #+#             */
/*   Updated: 2024/04/13 16:58:04 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while (*nptr != '\0' && (*nptr == 32 || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * res);
}

/* int	main(void)
{
	printf("%d\n", ft_atoi("0"));
	printf("%d\n", ft_atoi("546:5"));
	printf("%d\n", ft_atoi("-4886"));
	printf("%d\n", ft_atoi("+548"));
	printf("%d\n", ft_atoi("054854"));
	printf("%d\n", ft_atoi("000074"));
	printf("%d\n", ft_atoi("+-54"));
	printf("%d\n", ft_atoi("-+48"));
	printf("%d\n", ft_atoi("--47"));
	printf("%d\n", ft_atoi("++47"));
	printf("%d\n", ft_atoi("+47+5"));
	printf("%d\n", ft_atoi("-47-5"));
	printf("%d\n", ft_atoi("\e475"));
	printf("%d\n", ft_atoi("\t\n\r\v\f  469 \n"));
	printf("%d\n", ft_atoi("-2147483648"));
	printf("%d\n", ft_atoi("2147483647"));
	printf("%d\n", ft_atoi("\t\n\r\v\fd469 \n"));
	printf("%d\n", ft_atoi("\n\n\n  -46\b9 \n5d6"));
	printf("%d\n", ft_atoi(""));
}
 */
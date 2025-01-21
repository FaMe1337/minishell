/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:26:18 by toferrei          #+#    #+#             */
/*   Updated: 2025/01/21 11:51:25 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

static bool	check_flag(char *str)
{
	int	i;

	if (!str | str[0] != '-' | str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n');
		i++;
	return (str[i] == '\0');
}

int echo(char **strstr)
{
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:26:18 by toferrei          #+#    #+#             */
/*   Updated: 2025/01/21 12:06:33 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

static bool	check_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n');
		i++;
	return (str[i] == '\0');
}

int echo(char **strstr, t_data *data)
{
	bool	flag;
	int		i;

	i = 1;
	flag = false;
	if (strstr[1] && check_flag(strstr[1]))
	{
		i++;
		flag = true;
	}
	while (strstr[i] && check_flag[i])
		i++;
	while (strstr[i])
	{
		printf("%s", strstr[i]);
		if (strstr[i + 1] && ft_strlen(strstr[i]))
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}
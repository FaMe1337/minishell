/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:26:18 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/04 11:00:02 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

int echo(char **strstr, t_data *data)
{
	bool	flag;
	int		i;

	flag = false;
	if (strstr[1] && check_flag(strstr[i]))
	{
		flag = true;
		i++;
	}
	while ((strstr[i] && check_flag(strstr[i])))
		i++;
	while (strstr[i])
	{
		printf("%s", strstr[i]);
		if (strstr[i + 1] != NULL && ft_strlen(strstr[i]))
			write (1, " ", 1);
		i++;
	}
	if (!flag)
		write (1, "\n", 1);
	data->exit_code = 0;
}
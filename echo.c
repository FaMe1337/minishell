/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:26:18 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/21 14:48:04 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	check_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

<<<<<<< HEAD
int echo(char **strstr, t_data *data)
=======
void echo(char **strstr, t_data *data)
>>>>>>> tomaz
{
	bool	flag;
	int		i;

	i = 1;
	flag = false;
<<<<<<< HEAD
	if (strstr[1] && check_flag(strstr[1]))
	{
		i++;
		flag = true;
	}
	while (strstr[i] && check_flag[i])
=======
	if (strstr[1] && check_flag(strstr[i]))
	{
		flag = true;
		i++;
	}
	while ((strstr[i] && check_flag(strstr[i])))
>>>>>>> tomaz
		i++;
	while (strstr[i])
	{
		printf("%s", strstr[i]);
<<<<<<< HEAD
		if (strstr[i + 1] && ft_strlen(strstr[i]))
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}
=======
		if (strstr[i + 1] != NULL && ft_strlen(strstr[i]))
			write (1, " ", 1);
		i++;
	}
	if (!flag)
		write (1, "\n", 1);
	data->exit_code = 0;
}
>>>>>>> tomaz

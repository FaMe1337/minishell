/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:26:18 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/09 17:32:17 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	echo(char **strstr, t_data *data)
{
	bool	flag;
	int		i;

	i = 1;
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
		ft_putstr_fd(strstr[i], data->cmd_tree->fd_out);
		if (strstr[i + 1] != NULL && ft_strlen(strstr[i]))
			write (data->cmd_tree->fd_out, " ", 1);
		i++;
	}
	if (!flag && data->cmd_tree->fd_out <= 2)
		write (1, "\n", 1);
	data->exit_status = 0;
}

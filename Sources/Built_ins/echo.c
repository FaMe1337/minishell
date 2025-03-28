/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:26:18 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/28 14:32:42 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	echo(char **strstr, t_data *data, t_pipe *tree)
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
		ft_putstr_fd(strstr[i], tree->fd_out);
		if (strstr[i + 1] != NULL && ft_strlen(strstr[i]))
			write (tree->fd_out, " ", 1);
		i++;
	}
	if (!flag)
		write (tree->fd_out, "\n", 1);
	data->exit_status = 0;
}

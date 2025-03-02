/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:39:06 by famendes          #+#    #+#             */
/*   Updated: 2025/03/02 14:52:13 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo\0") == 0)
		return (1);
	else if (ft_strcmp(command, "cd\0") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd\0") == 0)
		return (1);
	else if (ft_strcmp(command, "env\0") == 0)
		return (1);
	else if (ft_strcmp(command, "export\0") == 0)
		return (1);
	else if (ft_strcmp(command, "unset\0") == 0)
		return (1);
	else if (ft_strcmp(command, "exit\0") == 0)
		return (1);
	return (0);
}

void	exec_builtin(char **cmd, t_data *data)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd();
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export();
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset();
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit();
}

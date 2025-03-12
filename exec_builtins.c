/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:39:06 by famendes          #+#    #+#             */
/*   Updated: 2025/03/12 01:42:17 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *command)
{
	write(1, "entredcsdfsf aqui\n", 19);
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
	else if (ft_strcmp(command, "thisexit\0") == 0)
		return (1);
	return (0);
}

void	exec_builtin(char **cmd, t_data *data)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		echo(cmd, data);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		change_directory(cmd, data);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd(data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		environment(cmd, data);
	else if (ft_strcmp(cmd[0], "export") == 0)
		export_bi(cmd, data);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		unset_env(cmd, data);
	else if (ft_strcmp(cmd[0], "exit") == 0)
			builtin_exit(cmd, data);
}

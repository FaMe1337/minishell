/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:39:57 by famendes          #+#    #+#             */
/*   Updated: 2025/03/08 12:31:39 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_solo_pipe(t_pipe *cmd_tree, t_data *data)
{

	if (is_builtin(cmd_tree->cmd[0]))
		exec_builtin(cmd_tree->cmd, data);
	else
	{
		cmd_tree->pid = fork();
		if (cmd_tree->pid == -1)
		{
			ft_putstr_fd("Error creating fork", 2);
			data->exit_status = 1;
			return;
		}
		if (cmd_tree->pid == 0)
		{
			child_process(cmd_tree, data);
		}
		//temos de resetar o terminal com sinais senão perco o readline
		waitpid(cmd_tree->pid, NULL, 0);
	}
}

void	executor(t_data *data)
{
	if (handle_redirections(data->cmd_tree))
	{
		data->exit_status = 1;
		return;
	}
	if (!data->cmd_tree->next)
		exec_solo_pipe(data->cmd_tree, data);
	else
	{
		//todo multiple pipes
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:39:57 by famendes          #+#    #+#             */
/*   Updated: 2025/02/16 22:35:26 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_data *data)
{
	if (handle_redirections(data->pipe_list));
	{
		data->exit_status = 1;
		return;
	}
/* 	if (!data->pipe_list->next)
		exec_solo_pipe(data->pipe_list, data);
	else
	{
		//todo multiple pipes
	} */
}

/* void	exec_solo_pipe(t_pipe *cmd, t_data *data)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		write(2, "Error creating fork", 20);
		data->exit_status = 1;
		return;
	}
	if (cmd->pid == 0)

} */

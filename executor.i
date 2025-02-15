/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:39:57 by famendes          #+#    #+#             */
/*   Updated: 2025/02/15 19:45:04 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_data *data)
{
	if (!data->pipe_list->next)
		exec_solo_pipe(data->pipe_list, data);
}

void	exec_solo_pipe(t_pipe *lst, t_data *data)
{
	lst->pid = fork();
	if (lst->pid == -1)
	{
		write(2, "Error creating fork", 20);
		data->exit_status = 1;
		return;
	}
	if (lst->pid == 0)
	
}

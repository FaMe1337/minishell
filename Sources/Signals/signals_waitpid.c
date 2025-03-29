/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_waitpid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:08:49 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/29 17:25:21 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_signaled(int status, t_data *data)
{
	if (WTERMSIG(status) == 2 && !data->signaled)
	{
		write(1, "\n", 1);
		write(1, "olaoalaoaoal\n", 14);
		data->signaled = true;
	}
	else if (WTERMSIG(status) == 3 && !data->signaled)
	{
		write(1, "Quit (no core dump)\n", 20);
		data->signaled = true;
	}
	data->exit_status = 128 + WTERMSIG(status);
}

void	ft_waitpid(int pid, t_data *data)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		data->exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		handle_signaled(status, data);
	else
		data->exit_status = 1;
}

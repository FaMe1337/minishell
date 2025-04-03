/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_waitpid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:08:49 by toferrei          #+#    #+#             */
/*   Updated: 2025/04/03 19:58:12 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_signaled(int status, t_data *data)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT && !data->signaled)
	{
		write(1, "\n", 1);
		data->signaled = true;
		printf("%d\n", data->cmd_tree->pid);
		if (data->cmd_tree->pid == -1)
			exit_exit(data, 128 + sig);

	}
	else if (sig == SIGQUIT && !data->signaled)
	{
		write(1, "Quit (no core dump)\n", 20);
		data->signaled = true;
	}
	minicall()->exit_status = 128 + sig;
	printf("fx ctrl c%d\n", data->exit_status);
}

void	ft_waitpid(int pid, t_data *data)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		printf("passei oaoalaoaoal \n");
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

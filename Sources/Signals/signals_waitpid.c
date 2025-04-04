/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_waitpid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:08:49 by toferrei          #+#    #+#             */
/*   Updated: 2025/04/04 20:29:21 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_heredoc(int sig)
{
	(void)sig;
	close(minicall()->tmp);
	write(STDOUT_FILENO, "\n", 1);
	minicall()->exit_status = 130;
	exit_exit(minicall(), 130);
}

static void	handle_signaled(int status, t_data *data)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT && !data->signaled)
	{
		write(1, "\n", 1);
		data->signaled = true;
	}
	else if (sig == SIGQUIT && !data->signaled)
	{
		write(1, "Quit (no core dump)\n", 20);
		data->signaled = true;
	}
	minicall()->exit_status = 128 + sig;
}

void	ft_waitpid(int pid, t_data *data)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		return ;
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		handle_signaled(status, data);
	else
		data->exit_status = 1;
}

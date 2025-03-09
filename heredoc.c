/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:24:16 by fabio             #+#    #+#             */
/*   Updated: 2025/03/09 14:59:59 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void write_heredoc(char *input, int wpipe)
{
	if (!*input)
		return;
	ft_putstr_fd(input, wpipe);
	write(wpipe, "\n", 1);
	free(input);
}

static void read_heredoc(char *str, t_pipe *cmd, t_data *data)
{
	char	*input;

	close(cmd->doc_pipe[0]);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			//write_for_terminal();
			break;
		}
		if (ft_strcmp(input, str) == 0)
		{
			free(input);
			break;
		}
		write_heredoc(input, cmd->doc_pipe[1]);
	}
	close(cmd->doc_pipe[1]);
	exit(0);
}

void	exec_doc(char *str, t_pipe *cmd, t_data *data)
{
	int	pid;
	int	status;

	if (pipe(cmd->doc_pipe) < 0)
	{
		perror("pipe error");
		cmd->bad_fd = true;
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("pid error");
		cmd->bad_fd = true;
		return;
	}
	else if (pid == 0)
		read_heredoc(str, cmd, data);
	close(cmd->doc_pipe[1]);
	waitpid(pid, &status, 0);
}

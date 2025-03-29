/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:24:16 by fabio             #+#    #+#             */
/*   Updated: 2025/03/29 23:03:25 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	expand_doc_token(t_token *token, t_data *data)
{
	int		i;
	t_token	*temp;

	temp = token;
	i = 0;
	while (temp->value[i])
	{
		if (temp->value[i] == '$' && !single_quote(temp->value, i) \
			&& temp->value[i + 1])
		{
			if (valid_expansion(temp->value, i))
			{
				expand_str(temp, data);
				continue ;
			}
		}
		i++;
	}
}

static char	*expand_doc(char *str, t_data *data)
{
	t_token	*token;
	char	*result;

	token = init_token(str);
	expand_doc_token(token, data);
	result = ft_strdup(token->value);
	free(token->value);
	free(token);
	return (result);
}

static void	write_heredoc(char *input, int wpipe, t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	if (!*input)
	{
		free(input);
		return ;
	}
	temp = ft_strdup(input);
	free(input);
	while (temp[i])
	{
		if (temp[i] == '$')
		{
			temp = expand_doc(temp, data);
			continue ;
		}
		i++;
	}
	ft_putstr_fd(temp, wpipe);
	write(wpipe, "\n", 1);
	free(temp);
}

static void	read_heredoc(char *str, t_pipe *cmd, t_data *data)
{
	char	*input;

	signal(SIGINT, SIG_DFL);
	if (cmd->doc_pipe[0] > 2)
		close(cmd->doc_pipe[0]);
	while (1)
	{
		input = readline("> ");
		if (!input)
			ctrl_d_msg_and_exit(input, str, cmd, data);
		if (ft_strcmp(input, str) == 0)
		{
			free(input);
			break ;
		}
		write_heredoc(input, cmd->doc_pipe[1], data);
	}
	close(cmd->doc_pipe[1]);
}

int	exec_doc(char *str, t_pipe *cmd, t_data *data)
{
	int	pid;

	if (cmd->doc_pipe[0] > 2)
		close(cmd->doc_pipe[0]);
	if (pipe(cmd->doc_pipe) < 0)
		return (pipe_error(cmd));
	pid = fork();
	if (pid == -1)
		return (pipe_error(cmd));
	else if (pid == 0)
		read_heredoc(str, cmd, data);
	set_parent_signals();
	close(cmd->doc_pipe[1]);
	ft_waitpid(pid, data);
	set_main_signals();
	if (data->exit_status == 130)
		return (-1);
	if (data->exit_status == 144)
		data->exit_status = 0;
	return (1);
}

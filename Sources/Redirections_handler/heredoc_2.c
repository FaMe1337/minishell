/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:05:08 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/26 19:37:09 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void check_last_red_in (t_pipe *cmd)
{
	int	i;

	i = 0;
	while (cmd->red && cmd->red[i])
	{
		if (ft_strncmp(cmd->red[i], "DOC:", 4) == 0)
			cmd->heredoc = true;
		else if (ft_strncmp(cmd->red[i], "RDI:", 4) == 0)
			cmd->heredoc = false;
		i++;
	}
}

void	pipe_error(t_pipe *cmd)
{
	perror("pid error");
	cmd->bad_fd = true;
	return ;
}

void	print_ctrl_d_msg(char *eof, t_data *data)
{
	char	*str;

	str = ft_itoa(data->line_nbr);
	write(2, "minishell: warning: here-document at line ", 42);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " delimited by end-of-file (wanted '", 35);
	write(2, eof, ft_strlen(eof));
	write(2, "')\n", 3);
}

void	ctrl_d_msg_and_exit(char *input, char *str, t_pipe *pipe, t_data *data)
{
	if (input != NULL)
		free(input);
	close(pipe->doc_pipe[1]);
	print_ctrl_d_msg(str, data);
	data->exit_status = 144;
	exit(144);
}

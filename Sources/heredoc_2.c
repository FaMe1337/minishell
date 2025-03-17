/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:05:08 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/17 14:15:31 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit(144);
}

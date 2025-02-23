/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:51:25 by famendes          #+#    #+#             */
/*   Updated: 2025/02/23 13:17:10 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append(char *str, t_pipe *cmd)
{
	int		fd;
	if (!str || !str[0])
	{
		ft_putstr_fd("No outfile present\n", 2);
		cmd->bad_fd = true;
		return (1);
	}
	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Invalid outfile\n", 2);
		cmd->bad_fd = true;
		return (1);
	}
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (0);
}

int	red_out(char *str, t_pipe *cmd)
{
	int		fd;
	if (!str || !str[0])
	{
		ft_putstr_fd("No outfile present\n", 2);
		cmd->bad_fd = true;
		return (1);
	}
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Invalid outfile\n", 2);
		cmd->bad_fd = true;
		return (1);
	}
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (0);
}

static int	parse_redirections(char *str, t_pipe *cmd)
{
	if (ft_strncmp(str, "DOC:", 4) == 0)
		//here_doc(str + 4, cmd);
		printf("ola");
	else if (ft_strncmp(str, "RDI:", 4) == 0)
		//red_in(str + 4, cmd);
		printf("ola");
	else if (ft_strncmp(str, "RDO:", 4) == 0)
		red_out(str + 4, cmd);
	else if (ft_strncmp(str, "APP:", 4) == 0)
		append(str + 4, cmd);
	if (cmd->bad_fd)
		return (1);
	return (0);
}

int	handle_redirections(t_pipe *cmd)
{
	int		i;

	if (!cmd)
		return (1);
	while (cmd)
	{
		i = 0;
		while(cmd->red && cmd->red[i])
		{
			if (parse_redirections(cmd->red[i], cmd))
				return (1);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:51:25 by famendes          #+#    #+#             */
/*   Updated: 2025/02/16 22:21:44 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_out(char *str, t_pipe *cmd)
{
	int		fd;
	char	*filename;

	if (!str && !str[0])
	{
		ft_putstr_fd("No outfile present\n", 2);
		cmd->bad_fd = true;
		return (1);
	}
	filename = str + 4;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Invalid outfile\n", 2);
		cmd->bad_fd = true;
		return (1);
	}
	return (0);
}

static int	parse_redirections(char *str, t_pipe *cmd)
{
	if (ft_strncmp(str, "DOC:", 4) == 0)
		here_doc(str, cmd);
	else if (ft_strncmp(str, "RDI:", 4) == 0)
		red_out(str, cmd);
	else if (ft_strncmp(str, "RDO:", 4) == 0)
		red_out(str, cmd);
	else if (ft_strncmp(str, "APP:", 4) == 0)
		append(str, cmd);
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

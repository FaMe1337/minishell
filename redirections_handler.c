/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:51:25 by famendes          #+#    #+#             */
/*   Updated: 2025/03/02 14:57:54 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append(char *str, t_pipe *cmd)
{
	int	fd;

	if (!str || !str[0])
	{
		ft_putstr_fd("No outfile present\n", 2);
		cmd->bad_fd = true;
		return ;
	}
	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
        ft_putstr_fd("minishell: ", 2);
        perror(str);
		cmd->bad_fd = true;
		return ;
	}
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = fd;
}

void	red_out(char *str, t_pipe *cmd)
{
	int	fd;

	if (!str || !str[0])
	{
		ft_putstr_fd("No outfile present\n", 2);
		cmd->bad_fd = true;
		return ;
	}
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
        ft_putstr_fd("minishell: ", 2);
        perror(str);
		cmd->bad_fd = true;
		return ;
	}
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = fd;
}

void	red_in(char *str, t_pipe *cmd)
{
	int	fd;

	if (!str || !str[0])
	{
		ft_putstr_fd("No infile present\n", 2);
		cmd->bad_fd = true;
		return ;
	}
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
        ft_putstr_fd("minishell: ", 2);
        perror(str);
		cmd->bad_fd = true;
		return ;
	}
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	cmd->fd_in = fd;
}

void	check_if_last(t_pipe *cmd)
{
	int i;

	i = 0;
	while (cmd->red)
	{
		if (ft_strncmp(cmd->red[i], "DOC:", 4) == 0)
			cmd->last_red_out = true;
		else if (ft_strncmp(cmd->red[i], "RDI:", 4) == 0)
			cmd->last_red_out = false;
		i++;
	}
}

static void	exec_doc(char *str, t_pipe *cmd)
{
	pipe(cmd->doc_pipe)
}

static int	parse_redirections(char *str, t_pipe *red)
{
	if (ft_strncmp(str, "DOC:", 4) == 0)
		{
			check_if_last(red);
			if (red->last_red_out)
				//exec_doc(str + 4, red);
				printf("ola\n");
		}
	else if (ft_strncmp(str, "RDI:", 4) == 0)
		red_in(str + 4, red);
	else if (ft_strncmp(str, "RDO:", 4) == 0)
		red_out(str + 4, red);
	else if (ft_strncmp(str, "APP:", 4) == 0)
		append(str + 4, red);
	if (red->bad_fd)
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

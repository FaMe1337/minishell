/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:51:25 by famendes          #+#    #+#             */
/*   Updated: 2025/04/03 21:26:22 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	append(char *str, t_pipe *cmd)
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

static void	red_out(char *str, t_pipe *cmd)
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

static void	red_in(char *str, t_pipe *cmd)
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

static int	parse_redirections(char *str, t_pipe *red)
{
	if (ft_strncmp(str, "RDI:", 4) == 0)
		red_in(str + 4, red);
	else if (ft_strncmp(str, "RDO:", 4) == 0)
		red_out(str + 4, red);
	else if (ft_strncmp(str, "APP:", 4) == 0)
		append(str + 4, red);
	if (red->bad_fd)
		return (1);
	return (0);
}

int	handle_redirections(t_pipe *cmd, t_data *data)
{
	int		i;

	i = 0;
	while (cmd->red && cmd->red[i])
	{
		if (ft_strncmp(cmd->red[i], "DOC:", 4) == 0)
			if (exec_doc(cmd->red[i] + 4, cmd, data) == -1)
				break ;
		i++;
	}
	i = 0;
	while (cmd->red && cmd->red[i])
	{
		if (parse_redirections(cmd->red[i], cmd))
		{
			data->exit_status = 1;
			return (1);
		}
		i++;
	}
	check_last_red_in(cmd);
	return (0);
}

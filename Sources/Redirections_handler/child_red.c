/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:57:55 by fabio             #+#    #+#             */
/*   Updated: 2025/03/30 16:13:41 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	close_fds(t_pipe *tree)
{
	if (tree->heredoc)
		dup2(tree->doc_pipe[0], STDIN_FILENO);
	else if (tree->fd_in > 2)
		dup2(tree->fd_in, STDIN_FILENO);
	if (tree->doc_pipe[0] > 2)
		close(tree->doc_pipe[0]);
	if (tree->fd_in > 2)
		close(tree->fd_in);
}

void	child_red_in(t_pipe *tree)
{
	int		i;
	bool	has_red;

	i = 0;
	printf("dentro do child red in o cmd é : %s\n", tree->cmd[0]);
	has_red = false;
	if (tree->red)
	{
		while (tree->red[i])
		{
			if (ft_strncmp(tree->red[i], "RDI:", 4) == 0 \
				|| ft_strncmp(tree->red[i], "DOC:", 4) == 0)
				has_red = true;
			i++;
		}
	}
	printf("has_read: %d\n", has_red);
	if (tree->previous != NULL)
	{
		if (!has_red){
			dup2(tree->previous->pipe[0], STDIN_FILENO);
			printf("entrei no previous\n");
		}
		close(tree->previous->pipe[0]);
	}
	if (has_red)
		close_fds(tree);
	if (!tree->previous)
		close(tree->pipe[0]);
}

void	child_red_out(t_pipe *tree)
{
	int		i;
	bool	has_red;

	i = -1;
	ft_putstr_fd("entrei no red out", 2);
	has_red = false;
	if (tree->red)
	{
		while (tree->red[++i])
		{
			if (ft_strncmp(tree->red[i], "RDO:", 4) == 0 \
				|| ft_strncmp(tree->red[i], "APP:", 4) == 0)
			{
				has_red = true;
				dup2(tree->fd_out, STDOUT_FILENO);
			}
		}
	}
	if (tree->next)
	{
		if (!has_red){
			dup2(tree->pipe[1], STDOUT_FILENO);
			printf("entrei dup do red out\n");
		}
		close(tree->pipe[1]);
	}
	if (!tree->next && tree->pipe[1] > 2)
		close(tree->pipe[1]);
}

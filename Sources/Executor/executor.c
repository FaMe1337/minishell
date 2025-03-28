/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:39:57 by famendes          #+#    #+#             */
/*   Updated: 2025/03/28 16:59:10 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	set_up_child(t_pipe *tree, t_data *data)
{
	if (pipe(tree->pipe) < 0)
	{
		ft_putstr_fd("Error creating pipe", 2);
		return (0);
	}
	tree->pid = fork();
	if (tree->pid == -1)
	{
		ft_putstr_fd("Error creating fork", 2);
		return (0);
	}
	if (tree->pid == 0)
		child_process(tree, data);
	close(tree->pipe[1]);
	if (tree->previous && tree->previous->pipe[0] > 2)
		close(tree->previous->pipe[0]);
	if (!tree->next && tree->pipe[0] > 2)
		close(tree->pipe[0]);
	return (1);
}

static void	exec_multiple_pipes(t_pipe *tree, t_data *data)
{
	int		status;
	t_pipe	*temp;

	temp = tree;
	while (tree)
	{
		if (handle_redirections(tree, data))
		{
			tree = tree->next;
			continue ;
		}
		if (!set_up_child(tree, data))
			return ;
		tree = tree->next;
	}
	while (temp)
	{
		waitpid(temp->pid, &status, 0);
		temp = temp->next;
	}
}

static void	exec_solo_pipe(t_pipe *cmd_tree, t_data *data)
{
	if ((!cmd_tree->cmd || !cmd_tree->cmd[0]))
		return ;
	if (handle_redirections(cmd_tree, data))
		return ;
	if (is_builtin(cmd_tree->cmd[0]))
		exec_builtin(cmd_tree->cmd, data, cmd_tree);
	else
	{
		set_signals_to_ignore();
		cmd_tree->pid = fork();
		if (cmd_tree->pid == -1)
		{
			ft_putstr_fd("Error creating fork", 2);
			data->exit_status = 1;
			return ;
		}
		if (cmd_tree->pid == 0)
		{
			set_signals_to_default();
			child_process(cmd_tree, data);
		}
		ft_waitpid(cmd_tree->pid, data);
	}
}

void	executor(t_data *data)
{
	if (!data->cmd_tree->next)
		exec_solo_pipe(data->cmd_tree, data);
	else
		exec_multiple_pipes(data->cmd_tree, data);
	set_main_signals();
}

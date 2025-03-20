/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_cleaning_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:46:00 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/20 16:16:27 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_all_fds(t_pipe *tree)
{
	if (!tree)
		return ;
	if (tree->fd_in > 2)
		close(tree->fd_in);
	if (tree->fd_out > 2)
		close(tree->fd_out);
	if (tree->doc_pipe[0] > 2)
		close(tree->doc_pipe[0]);
	if (tree->pipe[0] > 2)
		close(tree->pipe[0]);
	if (tree->pipe[1] > 2)
		close(tree->pipe[1]);
}

void	free_split_and_token(char **split, t_token *token)
{
	int		i;
	t_token	*temp;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	temp = token;
	while (token)
	{
		token = token->next;
		free(temp);
		temp = token;
	}
}

void	free_stuff(t_data *data)
{
	t_token	*current;
	t_pipe	*currentz;

	while (data->token)
	{
		current = data->token->next;
		free(data->token->value);
		free(data->token);
		data->token = current;
	}
	while (data->cmd_tree)
	{
		currentz = data->cmd_tree->next;
		clean_all_fds(data->cmd_tree);
		free_char_array(data->cmd_tree->cmd);
		free_char_array(data->cmd_tree->red);
		free(data->cmd_tree);
		data->cmd_tree = currentz;
	}
	data->signaled = false;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_cleaning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabio <fabio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:14:12 by famendes          #+#    #+#             */
/*   Updated: 2025/03/15 23:41:35 by fabio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_putstr_fd("Error allocating memory in Malloc\n", 2);
		return(NULL);
	}
	ft_memset(ret, '\0', size);
	return (ret);
}

void free_split_and_token(char **split, t_token *token)
{
	int	i;
	t_token *temp;

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

void free_all_data(t_data *data)
{
	if (!data)
		return;
	free(data->home);
	free(data->pwd);
	free(data->pwd_with_till);
	ft_clean_list(data->env);
	free_char_array(data->env_str_array);
}

void	free_stuff(t_data *data)
{
	t_token *current;
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
}

void clean_all_fds(t_pipe *tree)
{
	if (tree->fd_in > 2)
		close(tree->fd_in);
	if (tree->fd_out > 2)
		close(tree->fd_out);
	if (tree->doc_pipe[0] > 2)
		close(tree->doc_pipe[0]);
}

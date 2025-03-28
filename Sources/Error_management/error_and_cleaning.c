/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_cleaning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:14:12 by famendes          #+#    #+#             */
/*   Updated: 2025/03/28 02:01:02 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_putstr_fd("Error allocating memory in Malloc\n", 2);
		return (NULL);
	}
	ft_memset(ret, '\0', size);
	return (ret);
}

static void	clean_tokens(t_data *data)
{
	t_token	*current;

	if (!data->token)
		return ;
	while (data->token)
	{
		current = data->token->next;
		free(data->token->value);
		free(data->token);
		data->token = current;
	}
}

static void	clean_cmd_tree(t_data *data)
{
	t_pipe	*current;

	if (!data->cmd_tree)
		return ;
	while (data->cmd_tree)
	{
		current = data->cmd_tree->next;
		free_char_array(data->cmd_tree->cmd);
		free_char_array(data->cmd_tree->red);
		clean_all_fds(data->cmd_tree);
		free(data->cmd_tree);
		data->cmd_tree = current;
	}
}

void	exit_exit(t_data *data)
{
	int	code;

	if (data->pwd)
		free(data->pwd);
	if (data->home)
		free(data->home);
	if (data->pwd_with_till)
		free(data->pwd_with_till);
	ft_clean_list(data->env);
	free_char_array(data->env_str_array);
	clean_tokens(data);
	clean_cmd_tree(data);
	clean_all_fds(data->cmd_tree);
	clear_history();
	code = data->exit_status;
	exit(code);
}

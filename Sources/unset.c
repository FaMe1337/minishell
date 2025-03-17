/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:38:10 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/17 16:08:47 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_env **env, char *var_name)
{
	t_env	*temp;
	t_env	*cursor;

	if (!env || !*env)
		return ;
	cursor = *env;
	temp = check_for_variable(*env, var_name);
	if (cursor != temp)
	{
		while (cursor->next != temp)
			cursor = cursor->next;
		cursor->next = temp->next;
	}
	else
		*env = temp->next;
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	unset_env(char **args, t_data *data)
{
	int	i;

	i = 0;
	if (!args || !data->env)
	{
		data->exit_status = 1;
		return ;
	}
	while (args[++i])
		if (check_for_variable(*data->env, args[i]))
			delete_node(data->env, args[i]);
	data->exit_status = 0;
	update_prompt(data);
}

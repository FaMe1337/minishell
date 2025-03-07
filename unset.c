/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:38:10 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/06 15:30:04 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	delete_node(t_env *env, char *var_name)
{
	t_env	*temp;

	temp = check_for_variable(env, var_name);
	while (env->next != temp)
		env = env->next;
	env->next = temp->next;
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
		data->exit_code = 1;
		return ;
	}
	while (args[++i])
		if (check_for_variable(*data->env, args[i]))
			delete_node(*data->env, args[i]);
	data->exit_code = 0;
}

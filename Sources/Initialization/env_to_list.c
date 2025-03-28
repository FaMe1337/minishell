/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:43:46 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/28 18:25:21 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	populate_list(char *env, t_data *data)
{
	char	*temp1;
	t_env	*temp;

	temp1 = safe_malloc(sizeof * temp1 * ft_strlen(env) + 1);
	ft_strlcpy(temp1, env, size_until_symbol(env, '=') + 1);
	if (check_for_variable(*data->env, temp1))
	{
		temp = check_for_variable(*data->env, temp1);
		if (for_export(env))
		{
			free(temp->value);
			temp->value = ft_strdup(get_value_for_list(env));
			check_for_variable(*data->env, temp1)->exported = true;
		}
	}
	else
	{
		temp = ft_newnode(ft_strdup(temp1), \
			ft_strdup(get_value_for_list(env)), for_export(env));
		ft_modified_lstadd_back(data->env, temp);
	}
	free (temp1);
}

void	env_to_list(t_data *data, char **env)
{
	int		n;

	n = 0;
	if (!data->env)
	{
		data->env = safe_malloc(sizeof * data->env);
		*data->env = NULL;
	}
	while (env[n])
	{
		populate_list(env[n], data);
		n++;
	}
}

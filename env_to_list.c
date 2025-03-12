/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:43:46 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/12 15:11:09 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_of_envp(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i] != NULL)
		i++;
	return (i);
}

static void	populate_list(char *env, t_data *data)
{
	char	*temp1;
	t_env	*temp;

	temp1 = safe_malloc(sizeof * temp1 * ft_strlen(env) + 1);
	ft_strlcpy(temp1, env, size_until_symbol(env, '=') + 1);
	
	if (check_for_variable(*data->env, temp1))
	{
		temp = check_for_variable(*data->env, temp1);
		free(temp->value);
		temp->value = ft_strdup(get_value_for_list(env));
		check_for_variable(*data->env, temp1)->exported = true;
	}
	else
	{
		temp = ft_newnode(ft_strdup(temp1),
		ft_strdup(get_value_for_list(env)), \
		for_export(env));
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
	if (!size_of_envp(env))
		minimal_list_init(data);
	while (env[n])
	{
		populate_list(env[n], data);
		n++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:43:46 by toferrei          #+#    #+#             */
/*   Updated: 2025/03/09 19:13:10 by toferrei         ###   ########.fr       */
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

static void	populate_list(char *temp1, char *env, t_data *data)
{
	t_env	*temp;

	ft_strlcpy(temp1, env, size_until_symbol(env, '=') + 1);
	printf("%s", get_value_for_list(env));
	temp = ft_newnode(ft_strdup(temp1), \
		ft_strdup(get_value_for_list(env)), \
		for_export(env));
	if (check_for_variable(*data->env, temp1))
	{
		check_for_variable(*data->env, temp1)->value = \
			ft_strdup(get_value_for_list(env));
		check_for_variable(*data->env, temp1)->exported = true;
	}
	else
		ft_modified_lstadd_back(data->env, temp);
}

void	env_to_list(t_data *data, char **env)
{
	char	*temp1;
	int		n;

	n = 0;
	if (!data->env)
	{
		data->env = malloc(sizeof * data->env);
		*data->env = NULL;
	}
	if (!size_of_envp(env))
		minimal_list_init(data);
	while (env[n])
	{
		if (!check_for_variable(*data->env, env[n]))
		{
			unset_env((char *[]){"unset", env[n], NULL}, data);
			printf("estou aqui\n%s\n", env[n]);
		}
		temp1 = malloc (sizeof * temp1 * ft_strlen(env[n]) + 1);
		populate_list(temp1, env[n], data);
		n++;
		free (temp1);
	}
}

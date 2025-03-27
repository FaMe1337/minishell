/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:17 by famendes          #+#    #+#             */
/*   Updated: 2025/03/27 21:29:24 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**cpy_from_env(t_env **env)
{
	char	**res;
	t_env	*temp;
	int		i;
	char	*temp1;

	i = 0;
	temp = (*env);
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	res = safe_malloc(sizeof(char *) * (i + 1));
	temp = (*env);
	i = 0;
	while (temp)
	{
		temp1 = ft_strjoin(temp->name, "=");
		res[i++] = ft_strjoin(temp1, temp->value);
		free(temp1);
		temp = temp->next;
	}
	res[i] = 0;
	return (res);
}

static void	increase_shlvl(t_data *data)
{
	int		x;

	x = ft_atoi((check_for_variable(*data->env, "SHLVL")->value));
	x++;
	free(check_for_variable(*data->env, "SHLVL")->value);
	check_for_variable(*data->env, "SHLVL")->value = ft_itoa(x);
}

void	init_data(char **env, t_data *data)
{
	data->pwd = NULL;
	data->pwd = getcwd(NULL, 0);
	data->env = NULL;
	if (*env)
	{
		env_to_list(data, env);
		increase_shlvl(data);
	}
	else
		minimal_list_init(data);
	if (check_for_variable(*(data)->env, "HOME"))
		data->home = ft_strdup(check_for_variable(*(data)->env, "HOME")->value);
	else
		data->home = NULL;
	data->env_str_array = cpy_from_env(data->env);
	update_prompt(data);
	data->token = NULL;
	data->cmd_tree = NULL;
	data->exit_status = 0;
	data->line_nbr = 0;
	data->signaled = false;
}

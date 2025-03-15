/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:17 by famendes          #+#    #+#             */
/*   Updated: 2025/03/14 01:10:50 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


/* char *fetch_home(void)
{
	char	*cwd;
	char	*result;
	int	count;
	int	i;

	i = 0;
	count = 0;
	cwd = getcwd(NULL, 0);
	while (cwd[i])
	{
		if (cwd[i] == '/')
			count++;
		if (count == 3)
			break;
		i++;
	}
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	result[i] = '\0';
	while (--i >= 0)
		result[i] = cwd[i];
	free(cwd);
	return (result);
} */

/* char *get_prompt(void)
{
	char	*cwd;
	char	*result;
	int	i;
	int count;

	count = 0;
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd);
	while (cwd[--i] != '/' && i >= 0)
		count++;
	result = malloc(count + 5);
	if (!result)
		return (NULL);
	result[0] = '~';
	ft_strlcpy(result + 1, cwd + i, count + 2);
	ft_strlcat(result, "->", count + 5);
	free(cwd);
	return (result);
} */

void	increase_SHLVL(t_data *data)
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
	if (env)
	{
		env_to_list(data, env);
		increase_SHLVL(data);
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
}

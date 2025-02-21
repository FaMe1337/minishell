/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coisas_para_o_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:23:45 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/20 17:01:37 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_clean_list(t_env **lst)
{
	t_env *temp;
	t_env *temp2;

	temp = *lst;
	if (lst == NULL)
	{
		printf("Tried freeing empty list\n");
		return ;
	}
	while (temp != NULL)
	{
		temp2 = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = temp2;
	}
	free(lst); 
}

void	ft_print_list(t_env **lst, bool override)
{
	t_env *temp;

	temp = *lst;
	if (!lst)
	{
		printf("Tried printing empty list\n");
		return ;
	}
	while (temp != NULL)
	{
		printf("declare -x %s", temp->name);
		if (temp->exported)
			printf("=%s", temp->value);
		printf ("\n");
		temp = temp->next;
	}
}

t_env	*ft_modifiedlstlast(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_env	*ft_newnode(char *content, char *value, bool exported)
{
	t_env	*elem;

	elem = malloc(sizeof * elem);
	if (!elem)
		return (NULL);
	elem->name = content;
	elem->value = value;
	elem->exported = exported;
	elem->next = NULL;
	return (elem);
}

void	ft_modified_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = ft_modifiedlstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

t_env *check_for_variable(t_env *env, char *var_name)
{
	if (!env || !var_name || !var_name[0])
		return (NULL);
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, var_name, ft_strlen(var_name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

size_t size_until_symbol(char * str, char c)
{
	int n = 0;

	if (!str || !c)
		return (0);
	while (str[n] && str[n] != c)
		n++;
	return (n);
}

char *get_value_for_list(char * str)
{
	int n = 0;

	while (str[n] != '\0' && str[n - 1] != '=')
		n++;
	return (&str[n]);
}

bool for_export(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}

int	size_of_envp(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i] != NULL)
		i++;
	return (i);
}

void	env_to_list(t_data *data, char **env, int n)
{
	t_env *temp;
	char *temp1;

	if (!data->env)
	{
		data->env = malloc(sizeof * data->env);
		*data->env = NULL;
	}
	if (!size_of_envp(env))
		minimal_list_init(data);
	while (env[n])
	{
		temp1 = malloc (sizeof * temp1 * ft_strlen(env[n]) + 1);
		ft_strlcpy(temp1, env[n], size_until_symbol(env[n], '=') + 1);
		temp = ft_newnode(ft_strdup(temp1), ft_strdup(get_value_for_list(env[n])), for_export(env[n]));
		if (check_for_variable(*data->env, temp1)) // node exists
		{
			check_for_variable(*data->env, temp1)->value = ft_strdup(get_value_for_list(env[n]));
			check_for_variable(*data->env, temp1)->exported = true;
		}
		else
			ft_modified_lstadd_back(data->env, temp);
		n++;
		free (temp1);
	}
}

char *get_var_value(t_env *env, char *var_name)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, var_name, ft_strlen(var_name)))
			return (env->value);
		env= env->next;
	}
	return (NULL);
}

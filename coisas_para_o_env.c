/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coisas_para_o_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:23:45 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/04 12:32:08 by toferrei         ###   ########.fr       */
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
	while (temp->next != NULL)
	{
		temp2 = temp->next;
		free(temp->name);
		free(temp);
		temp = temp2;
	}
	free(temp->name);
	free(temp);
}

void	ft_print_list(t_env **lst)
{
	t_env *temp;

	temp = *lst;
	if (lst == NULL)
	{
		printf("Tried printing empty list\n");
		return ;
	}
	while (temp->next != NULL)
	{
		printf("%s=", temp->name);
		printf("%s\n", temp->value);
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
	while (env->next != NULL)
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
	{
		n++;
	}
	return (n);
}

char *get_value_for_list(char * str)
{
	int n = 0;


	while (str[n] != '\0' && str[n - 1] != '=')
		n++;
	return (&str[n]);
}

void	env_to_list(t_data *data, char **env)
{
	t_env *temp;
	char *temp1;

	int n = 0;
	if (!data->env)
	{
		data->env = malloc(sizeof * data->env);
		*data->env = NULL;
	}
	while (env[n])
	{
		temp1 = malloc (sizeof * temp1 * ft_strlen(env[n]) + 1);
		ft_strlcpy(temp1, env[n], size_until_symbol(env[n], '=') + 1);
		temp = ft_newnode(ft_strdup(temp1), get_value_for_list(env[n]), true);
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
		{
			return (env->value);
		}
		env= env->next;
	}
	return (NULL);
}